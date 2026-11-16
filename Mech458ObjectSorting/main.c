#include "adc.h"
#include "breadboard_io.h"
#include "dcmotor.h"
#include "lcd.h"
#include "linkedqueue.h"
#include "mtimer.h"
#include "myutils.h"
#include "stepper.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

volatile char STATE;

int main(int argc, char *argv[])
{

    CLKPR = 0x80;
    CLKPR = 0x01;

    link *head;
    link *tail;
    setup(&head, &tail);

    STATE = 0;

    cli();

    EICRA |= _BV(ISC01) | _BV(ISC00);
    // EIMSK |= _BV(INT0);

    EICRA |= _BV(ISC11);
    EIMSK |= _BV(INT1);

    EICRA |= _BV(ISC21) | _BV(ISC20);
    EIMSK |= _BV(INT2);

    EICRA |= _BV(ISC31);
    EIMSK |= _BV(INT3);

    init_breadboard_io();
    init_dcmotor(DUTY_50_PERCENT, PRESCALER_3kHZ);
    // initialize adc
    init_adc(ONE_SHOT, AVCC, ADC_IRQ_ENABLE, ADC_10_BITS);
    // Initialize LCD module ; no blink or underline
    InitLCD(LS_BLINK | LS_ULINE);
    LCDClear();
    // initialize the FIFO
    //	EICRA &= ~_BV(ISC21) & ~_BV(ISC20); /* These lines would undo the above
    // two lines */ 	EICRA &= ~_BV(ISC31) & ~_BV(ISC30); /* Nice little trick
    // */

    // See page 112 - EIFR External Interrupt Flags...notice how they reset on
    // their own in 'C'...not in assembly

    // Enable all interrupts
    sei(); // Note this sets the Global Enable for all interrupts
    // home the bucket
    while ((PIND & 0x2) != 0)
        ;
    home_on_black();
    forward();

POLLING_STAGE:
    PORTL = 0 << 4;
    switch (STATE)
    {
    case (0):
        goto POLLING_STAGE;
    case (1):
        goto REFLECTIVE_STAGE;
    case (2):
        goto BUCKET_STAGE;

        break;
    case (3):
        goto END;
    default:
        goto POLLING_STAGE;
    }

REFLECTIVE_STAGE:
    // Do whatever is necessary HERE
    PORTL = 1 << 4;
    LCDClear();
    uint16_t min_Reading = 1023;

    // while an object is infront of sensor
    while ((PIND & OR) != 0)
    {
        uint16_t result = read_adc();
        if (result < min_Reading)
        {
            min_Reading = result;
        }
    }
    link *NewLink;
    initLink(&NewLink);
    // Display min_Reading
    LCDWriteStringXY(0, 0, "CODE:");
    LCDWriteIntXY(7, 0, min_Reading, 4);
    if (min_Reading < 283)
    {
        // found aluminum!
        NewLink->e.itemCode = ALUMINIUM;
        LCDWriteStringXY(0, 1, "ALUMINUM");
    }
    else if (min_Reading < 727)
    {
        // found steel!
        NewLink->e.itemCode = STEEL;
        LCDWriteStringXY(0, 1, "STEEL");
    }
    else if (min_Reading < 956)
    {
        // found white!
        NewLink->e.itemCode = WHITE;
        LCDWriteStringXY(0, 1, "WHITE");
    }
    else
    {
        NewLink->e.itemCode = BLACK;
        LCDWriteStringXY(0, 1, "BLACK");
    }
    enqueue(&head, &tail, &NewLink);

    // Reset the state variable
    STATE = 0;
    goto POLLING_STAGE;

BUCKET_STAGE:
    PORTL = 2 << 4;
    break_hi();
    link *current_object = NULL;
    dequeue(&head, &current_object);
    if (isEmpty(&head))
    {
        tail = NULL;
    }
    if (current_object == NULL)
    {

        forward();
        STATE = 0;
        goto POLLING_STAGE;
    }

    // LCDWriteInt(current_object->e.itemCode, 1);
    TargetStep target = object_type_to_target_step(current_object->e.itemCode);
    free(current_object);
    int16_t dif = (int16_t)target - (int16_t)steps_from_home;
    if (dif > 100)
    {
        dif -= 200;
    }
    else if (dif < -100)
    {
        dif += 200;
    }
    uint8_t dir = (dif >= 0) ? CW : CCW;
    stepper_step = rotate(dir, (uint8_t)absolute(dif), stepper_step);
    steps_from_home = target;
    LCDWriteIntXY(9, 1, steps_from_home, 3);
    forward();
    STATE = 0;
    goto POLLING_STAGE;

END:
    PORTL = 3 << 4;
    return (0);
}

ISR(INT0_vect) { STATE = 0; }

ISR(INT1_vect) { STATE = 0; }

ISR(INT2_vect) { STATE = 1; }

ISR(INT3_vect) { STATE = 2; }

ISR(BADISR_vect) {}