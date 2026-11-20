/* dcmotor.h
 * DC motor driver for the ATmega2560
 * - Controls DC motor direction using the motor driver input pins
 * - Supports forward, reverse, and braking operation
 * - Generates PWM using Timer 0 in Fast PWM mode
 * - Configures PWM duty cycle and timer prescaler
 * - Maintains a direction flag to track conveyor direction
 *
 * Timer 0 is configured in Fast PWM mode with output compare A enabled.
 * The PWM frequency is determined by the system clock, timer prescaler,
 * and 8-bit timer resolution:
 *
 * f_PWM = f_clk / (N * 256)
 *
 * The PWM output is used to control the DC motor speed through the motor
 * driver. Direction is controlled independently through the motor input pins.
 *
 * MECH 458, Fall 2026, Khephren Gould & Clifton Tollefson
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "mtimer.h"
#include <stdint.h>

/* DUTY_50_PERCENT
 * PWM duty cycle count corresponding approximately to 50% duty cycle.
 * Timer 0 is an 8-bit timer, so the duty cycle ranges from 0 to 255.
 */
#define DUTY_50_PERCENT (128)

/* PRESCALER_3kHZ
 * Timer 0 prescaler value used to configure the PWM frequency.
 * The actual PWM frequency depends on the MCU clock frequency.
 */
#define PRESCALER_3kHZ (8)

/* forward
 * Drives the DC motor in the forward direction, corresponding to
 * counter-clockwise motor rotation and forward conveyor motion.
 */
void forward();

/* reverse
 * Drives the DC motor in the reverse direction, corresponding to
 * clockwise motor rotation and backward conveyor motion.
 */
void reverse();

/* break_hi
 * Applies electrical braking to the DC motor by driving both motor
 * direction inputs high while keeping the enable signals asserted.
 */
void break_hi();

/* set_direction_flag
 * Sets the direction flag to indicate that the conveyor is moving
 * in the forward direction.
 */
void set_direction_flag();

/* clear_direction_flag
 * Clears the direction flag to indicate that the conveyor is moving
 * in the reverse direction.
 */
void clear_direction_flag();

/* is_direction_flag
 * Returns the current state of the motor direction flag.
 *
 * Returns 1 if the direction flag is set, or 0 if it is cleared.
 */
uint8_t is_direction_flag();

/* init_dcmotor
 * Initializes Timer 0 for Fast PWM operation and configures the PWM
 * duty cycle and clock prescaler.
 *
 * duty_cycle_counts: PWM duty cycle count (0-255), where 0 corresponds
 *                    to 0% duty cycle and 255 corresponds approximately
 *                    to 100% duty cycle.
 * prescaler: Timer 0 clock prescaler (8, 64, 256, or 1024).
 *
 * Configures the PWM output on OC0A and sets the initial duty cycle.
 */
void init_dcmotor(uint8_t duty_cycle_counts, uint16_t prescaler);

#endif /* DCMOTOR_H_ */