/* stepper.h
 *  Stepper motor driver for the ATmega2560
 * - Timer 0 Fast PWM on OC0A to set the motor drive (duty cycle and frequency)
 * - Full stepping of a 2 coil stepper through PORTA using a 4 step table
 * - Homing using the hall effect sensor
 *
 * MECH 458, Fall 2026, Khephren Gould & Clifton Tollefson  */

#ifndef STEPPER_H
#define STEPPER_H

#include "avr/io.h"
#include "myutils.h"

// Degrees per step = 1.8°
// 200 steps for 360 degrees

// Rotation directions for rotate()
#define CW 1
#define CCW 0
// define as extern so main and other files can check how far away we are from
// home
extern uint8_t current_region;

extern uint8_t stepper_step;

extern const table_entry rotation_table[4][4];

/* init_stepper
 * Puts Timer 0 in Fast PWM mode (non-inverting on OC0A), sets the prescaler and
 * sets the initial duty cycle. The PWM frequency is f = f_clk / (prescaler *
 * 256).
 *
 * duty_cycle_counts: Value written to OCR0A (0-255). Duty cycle is counts /
 * 256. prescaler: Timer 0 clock prescaler. Must be 8, 64, 256 or 1024. Any
 * other value leaves the timer clock off, so no PWM is produced.
 */
void init_stepper(uint8_t duty_cycle_counts, uint16_t prescaler);

/* rotate
 * Steps the motor the given number of steps in the given direction by writing
 * the PORTA pattern for each step, moving through the 4 step sequence.
 *
 * dir: CW or CCW
 * steps: Number of steps to take
 * current_step: The step (1-4) the motor is currently on
 *
 * Returns the step (1-4) the motor ends on. Pass this back in as current_step
 * on the next call.
 */
uint8_t rotate(uint8_t dir, uint8_t steps, uint8_t current_step);

/* set_duty_cycle
 * Changes the PWM duty cycle by writing OCR0A. Takes effect immediately.
 *
 * duty_cycle_counts: New OCR0A value (0-255). Duty cycle is counts / 256.
 */
void set_duty_cycle(uint8_t duty_cycle_counts);

/* home_on_black
 * Rotates the motor CW one step at a time until the hall effect sensor
 * (HE_SENSOR_MASK on PINF) reads low, then stops and records the step in
 * stepper_count. Not finished yet.
 *
 * Returns an int8_t status (not implemented yet).
 */
int8_t home_on_black(void);

/* s_curve_50
 * Rotates the stepper 50 full steps (90 degrees at 1.8 degrees per step) using
 * an S-curve speed profile.
 *
 * The delay after each step comes from scurve_50_us[], a 50 entry table
 * generated in MATLAB.
 *
 * dir: CW or CCW
 * current_step: The step (1-4) of the 4 step sequence the coils are currently
 *               energized on.
 *
 * Returns the step (1-4) the motor ends on. Pass it back in as current_step on
 * the next call (main keeps it in stepper_step).
 *
 * Use for moves between adjacent bucket regions. For the opposite region, use
 * s_curve_100().
 */
uint8_t s_curve_50(uint8_t dir, uint8_t current_step);

/* s_curve_100
 * Same as s_curve_50 but for 100 steps (180 degrees), using scurve_100_us[].
 *
 * dir, current_step and the return value are the same as for s_curve_50().
 */
uint8_t s_curve_100(uint8_t dir, uint8_t current_step);
#endif