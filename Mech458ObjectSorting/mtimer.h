/* mtimer.h
 *  Timer driver for the ATmega2560
 * - Blocking millisecond (mTimer) and microsecond (uTimer) delays using
 *   Timer 1 in CTC mode with a prescaler of 8, polling the compare match flag
 * - Non blocking one shot timer on Timer 4 and auto reload timer on Timer 3
 * (CTC mode, prescaler 1024) that set the tim4_exp and tim3_exp flags from
 * their compare match ISRs
 * - Timings assume the 8 MHz system clock (16 MHz divided by 2 through CLKPR)
 *
 * MECH 458, Fall 2026, Khephren Gould & Clifton Tollefson  */

#ifndef MTIMER_H
#define MTIMER_H
#include "avr/io.h"

/* tim3_exp, tim4_exp
 * Flags set to 1 by the Timer 3 (auto reload) and Timer 4 (one shot) compare
 * match ISRs when their period expires. The ISRs only set them, so the main
 * code must clear them back to 0 after handling the event.
 */
extern volatile uint8_t tim3_exp;
extern volatile uint8_t tim4_exp;

/* mTimer
 * Blocking delay in milliseconds using Timer 1 in CTC mode with a prescaler of
 * 8. With the 8 MHz system clock (CLKPR divides the 16 MHz clock by 2), the
 * timer ticks at 1 MHz and OCR1A = 0x03EB gives about 1.004 ms per count.
 *
 * count: Number of milliseconds to wait (0-65535)
 *
 * Polls OCF1A and returns once count periods have passed, so it needs no
 * interrupts. Timer 1 is shared with uTimer(), so only one blocking delay can
 * run at a time.
 */
void mTimer(uint16_t count);

/* uTimer
 * Blocking delay in microseconds using Timer 1 in CTC mode with a prescaler of
 * 8. With the 8 MHz system clock the timer ticks at 1 MHz, so OCR1A = count
 * gives a delay of about count us.
 *
 * count: Number of microseconds to wait (0-65535)
 *
 * Polls OCF1A and returns when the compare match occurs. The function call
 * overhead adds a few us, which matters only for very short delays. Used by the
 * S-curve step delays.
 */
void uTimer(uint16_t count);

/* mstartTimerAutoReload
 * Starts a periodic timer on Timer 3 (CTC mode, prescaler 1024) and returns
 * immediately. Each time the period expires the ISR sets tim3_exp, and the
 * timer restarts on its own.
 *
 * period_millis: Period in milliseconds. Values are limited to 1-8191, and the
 *                maximum is about 8.2 s with the 8 MHz clock.
 *
 * The timer keeps running until mtimerInit() stops it. The period is about
 * 2.4% longer than requested (see note below).
 */
void mstartTimerAutoReload(uint16_t period_millis);

/* mstartTimerOneShot
 * Starts a single-shot timer on Timer 4 (CTC mode, prescaler 1024) and returns
 * immediately. When the time expires the ISR sets tim4_exp and the timer
 * stops.
 *
 * millis: Delay in milliseconds. Values are limited to 1-8191, and the maximum
 *         is about 8.2 s with the 8 MHz clock.
 *
 * Clear tim4_exp before starting a new one-shot, or an old expiry will look
 * like a new one.
 */
void mstartTimerOneShot(uint16_t millis);

/* mtimerInit
 * Stops Timer 1, Timer 3 and Timer 4 by clearing their clock select bits.
 * Interrupt masks and the tim3_exp and tim4_exp flags are not changed.
 */
void mtimerInit(void);

#endif
