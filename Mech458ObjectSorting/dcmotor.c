/*
 * dcmotor.c
 *
 * Created: 10/26/2026 10:27:03 PM
 *  Author: cliftontollefson
 */
#include "dcmotor.h"
#include "avr/interrupt.h"
#include "avr/io.h"

uint8_t direction_flag = 0;

void init_dc_motor() { DDRB = 0xFF; } // sets direction of port B to output
// Function that turns the DC motor counter clockwise, turning the conveyor
// forwards
void forward() { PORTB = (INB | ENA | ENB); }

// function that turns DC motor clockwise, turning the conveyor backwards
void reverse() { PORTB = (INA | ENA | ENB); }

// Function stops the DC motor
void break_hi() { PORTB = (INA | INB | ENA | ENB); }

void set_direction_flag()
{
    // PORTL =
    direction_flag = 1;
}

void clear_direction_flag() { direction_flag = 0; }

uint8_t is_direction_flag() { return direction_flag; }
