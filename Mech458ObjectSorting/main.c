#include "breadboard_io.h"
#include "dcmotor.h"
#include "linkedqueue.h"
#include "mtimer.h"
#include "stepper.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

volatile char STATE;

int main(int argc, char *argv[])
{
    link *head;
    link *tail;
    setup(&head, &tail);

    link *nl;
    initLink(&nl);
    nl->e.itemCode = WHITE;
    enqueue(&head, &tail, &nl);

    link *nl2;
    initLink(&nl2);
    nl2->e.itemCode = STEEL;
    enqueue(&head, &tail, &nl2);

    link *nl3;
    initLink(&nl3);
    nl2->e.itemCode = BLACK;
    enqueue(&head, &tail, &nl3);

    link *nl4;
    initLink(&nl4);
    nl2->e.itemCode = ALUMINIUM;
    enqueue(&head, &tail, &nl4);

    CLKPR = 0x80;
    CLKPR = 0x01;

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

    EIFR = 0x0F;
    sei();

    while ((PIND & 0x2) != 0)
        ;
    forward();
    home_on_black();

POLLING_STAGE:
    PORTL = 0 << 4;
    PORTC = PIND & 0x8;
    switch (STATE)
    {
    case (0):
        goto POLLING_STAGE;
    case (1):
        goto REFLECTIVE_STAGE;
    case (2):
        goto BUCKET_STAGE;
    case (3):
        goto END;
    default:
        goto POLLING_STAGE;
    }

REFLECTIVE_STAGE:
    PORTL = 1 << 4;
    STATE = 0;
    goto POLLING_STAGE;

BUCKET_STAGE:
    PORTL = 2 << 4;
    PORTC = PIND & 0x8;
    break_hi();
    link *current_object = NULL;
    dequeue(&head, &current_object);
    if (isEmpty(&head))
    {
        tail = NULL;
    }
    if (current_object == NULL)
    {
        STATE = 0;
        goto POLLING_STAGE;
    }
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