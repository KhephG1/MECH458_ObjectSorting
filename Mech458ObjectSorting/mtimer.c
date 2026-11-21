/* mtimer.c
 *  Timer driver for the ATmega2560
 * - Blocking millisecond (mTimer) and microsecond (uTimer) delays using
 *   Timer 1 in CTC mode with a prescaler of 8, polling the compare match flag
 * - Non blocking one shot timer on Timer 4 and auto reload timer on Timer 3
 * (CTC mode, prescaler 1024) that set the tim4_exp and tim3_exp flags from
 * their compare match ISRs
 * - Timings assume the 8 MHz system clock (16 MHz divided by 2 through CLKPR)
 *
 * MECH 458, Fall 2026, Khephren Gould & Clifton Tollefson  */

#include "mtimer.h"
#include <avr/interrupt.h>
#include <avr/io.h>
// on avr you can use the ISR macro to assign a handler for your interrupts
// you give the macro the vector that you would like your ISR to be triggered
// for

// oneshot timer
volatile uint8_t tim4_exp = 0;
ISR(TIMER4_COMPA_vect)
{
    TCCR4B = 0;
    tim4_exp = 1;
}
// autoreload timer
volatile uint8_t tim3_exp = 0;
ISR(TIMER3_COMPA_vect)
{
    // set tim_3_exp flag to 1
    tim3_exp = 1;
}

static inline uint16_t ms_to_ocr(uint16_t ms)
{
    if (ms > 8191)
        ms = 8191;
    if (ms == 0)
        ms = 1;
    return (ms << 3) - 1;
}

// an asynchronous one shot timer using the TIM2 peripheral
// IMPORTANT: Max time is 8.19 seconds (with 8Mhz system clock)
void mstartTimerOneShot(uint16_t millis)
{
    tim3_exp = 0;
    uint16_t counts = ms_to_ocr(millis);
    // enable output compare interrupts
    TIMSK4 |= _BV(OCIE4A);
    // set the output compare register to the desired counts
    OCR4A = counts;
    // clear any stale OCR interrupt flags
    TIFR4 = _BV(OCF4A);
    // ensure timer starts at 0
    TCNT4 = 0x0000;
    // start the timer with 1024 prescaler
    TCCR4B = _BV(WGM42) | _BV(CS42) | _BV(CS40);
}
// an asynchronous autoreload timer using the TIM3 peripheral
// IMPORTANT: Max time is 8.19 seconds (with 8Mhz system clock)
void mstartTimerAutoReload(uint16_t period_millis)
{
    tim4_exp = 0;
    uint16_t counts = ms_to_ocr(period_millis);
    // configure timer for autoreload mode
    TCCR3B |= _BV(WGM32);
    // enable output compare interrupts
    TIMSK3 |= _BV(OCIE3A);
    // set the output compare register to the desired counts
    OCR3A = counts;
    // clear any stale OCR interrupts
    TIFR3 = _BV(OCF3A);
    // ensure timer starts at 0
    TCNT3 = 0x0000;
    // start the timer with 1024 prescaler
    TCCR3B = _BV(WGM32) | _BV(CS32) | _BV(CS30);
}

void uTimer(uint16_t count)
{
    TCCR1B |= _BV(WGM12); // CTC mode
    TCCR1B |= _BV(CS11);  // prescaler 8
    OCR1A = count;
    TIFR1 = _BV(OCF1A); // clear compare flag
    TCNT1 = 0;
    while ((TIFR1 & 0x02) != 0x02)
        ; // busy wait
}
// A blocking timer implementation that uses the TIM1 peripheral
void mTimer(uint16_t count)
{
    uint16_t i = 0;
    // Set the Waveform gen. mode bit description to clear on compare mode only
    TCCR1B |= _BV(WGM12);
    TCCR1B |= _BV(CS11);
    // Set output compare register for 1000 cycles, 1ms
    OCR1A = 0x03EB;
    // enable output compare interrupts by unmasking them
    // TIMSK1 |= 0x02;
    // clear the interrupt for output compare
    TIFR1 = _BV(OCF1A);
    // clear the timer count before starting
    TCNT1 = 0x0000;
    // start the timer with a prescaler of 8

    while (i < count)
    {
        // poll the flag register for ocr flag
        if ((TIFR1 & 0x02) == 0x02)
        {
            // clear the flag
            TIFR1 = _BV(OCF1A);
            // 1ms has passed, increment count
            i++;
        }
    }

    return;
}
