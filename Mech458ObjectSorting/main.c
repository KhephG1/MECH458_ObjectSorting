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

// global variable holds current state of system
volatile State STATE;

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
    EIMSK |= _BV(INT0);

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
    // Initialize LCD module
    InitLCD(LS_BLINK | LS_ULINE);
    LCDClear();
    sei(); // Note this sets the Global Enable for all interrupts
    // wait for start button
    while ((PIND & 0x2) != 0)
        ;
    // home the bucket
    home_on_black();
    // start the belt
    forward();

POLLING_STAGE:
    PORTL = 0 << 4;
    switch (STATE)
    {
    case (POLLING):
        goto POLLING_STAGE;
        break;
    case (REFLECTIVE):
        goto REFLECTIVE_STAGE;
        break;
    case (BUCKET):
        goto BUCKET_STAGE;
        break;
    case (PAUSED):
        goto PAUSED;
        break;
    case (RAMPDOWN):
        goto END;
        break;
    default:
        goto POLLING_STAGE;
        break;
    }

REFLECTIVE_STAGE:
    // set status LED for reflective stage
    PORTL = 1 << 4;

    LCDClear();

    // variable to store lowest val seen by ADC
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
    STATE = POLLING;
    goto POLLING_STAGE;

BUCKET_STAGE:
    // set status LED for bucket stage
    PORTL = 2 << 4;
    // an object has hit the EX sensor: stop the belt
    break_hi();
    link *current_object = NULL;
    dequeue(&head, &current_object);
    // if we just emptied the list be sure to reset tail!
    if (isEmpty(&head))
    {
        tail = NULL;
    }
    // if this function is called but no elements are in the list,
    // go back to polling stage
    if (current_object == NULL)
    {
        forward();
        STATE = POLLING;
        goto POLLING_STAGE;
    }

    // LCDWriteInt(current_object->e.itemCode, 1);
    ObjectType target = current_object->e.itemCode;
    // look in the rotation table for the amount of steps and direction we need
    // to rotate
    table_entry entry = rotation_table[current_region][target];
    if (entry.steps == 50)
    {
        stepper_step = s_curve_50(entry.dir, stepper_step);
    }
    else if (entry.steps == 100)
    {
        stepper_step = s_curve_100(entry.dir, stepper_step);
    }
    // update the current region to the one we just rotated to
    current_region = target;
    LCDWriteIntXY(9, 1, current_region, 3);
    forward();
    // make sure to free the memory for the link
    free(current_object);
    STATE = POLLING;
    goto POLLING_STAGE;

PAUSED:
    STATE = POLLING;
    // todo implement paused
    goto POLLING_STAGE;

END:
    PORTL = 3 << 4;
    // todo implement end
    return (0);
}

ISR(INT0_vect) { STATE = PAUSED; }

ISR(INT1_vect) { STATE = RAMPDOWN; }

ISR(INT2_vect) { STATE = REFLECTIVE; }

ISR(INT3_vect) { STATE = BUCKET; }

ISR(BADISR_vect)
{
    PORTL = 0xFF; // turn all status LED on
    // trap the program here
    while (1)
        ;
}
