/*
 * dcmotor.c
 *
 * Created: 10/26/2026 10:27:03 PM
 *  Author: cliftontollefson
 */
#include "dcmotor.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "breadboard_io.h"

uint8_t direction_flag = 0;

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

static void init_TIM0()
{
    // put TIM0 in Fast PWM mode (Step 1)
    TCCR0A |= (_BV(WGM00) | _BV(WGM01));
    // Enable output compare A interrupt (step 2)
    // TIMSK0 |= _BV(OCIE0A);
    // Clear on compare match (step 3)
    TCCR0A |= _BV(COM0A1);
}

static void init_pwm(uint8_t duty_cycle_counts, uint16_t prescaler)
{
    // Set the TIM0 clock prescaler (step 4)
    //  The waveform frequency is f = f(clk,io) / (N*256)
    //  where fclk,io is the MCU frequency, N is the prescaler
    switch (prescaler)
    {
    case 1024:
        TCCR0B |= _BV(CS02) | _BV(CS00);
        break;
    case 256:
        TCCR0B |= _BV(CS02);
        break;
    case 64:
        TCCR0B |= _BV(CS01);
        break;
    case 8:
        TCCR0B |= _BV(CS00);
    default:
        // in future should print error since this means f = 31.25kHz which is
        // faster than motor supports
        break;
    }

    // set the duty cycle to 50%	(step 5)
    OCR0A = duty_cycle_counts;
}

void init_dcmotor(uint8_t duty_cycle_counts, uint16_t prescaler)
{
    init_TIM0();
    init_pwm(duty_cycle_counts, prescaler);
}

void set_duty_cycle(uint8_t duty_cycle_counts) { OCR0A = duty_cycle_counts; }