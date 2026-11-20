/* breadboard_io.h
 * Breadboard I/O driver for the ATmega2560
 * - Initializes GPIO direction registers for LEDs, motors, sensors, and
 *   push buttons
 * - Provides functions to write to the red and yellow/green LED banks
 * - Provides functions to read push button states with configurable polarity
 * - Defines pin assignments for DC motors, stepper motors, sensors, LEDs,
 *   and push buttons
 *
 * Port assignments:
 * - Port A: Stepper motor control signals (output)
 * - Port B: DC motor control signals, including PWM (output)
 * - Port C: Red LEDs and LCD interface (output)
 * - Port D: Push buttons and optical sensor (input)
 * - Port F: ADC input and HE sensor (input)
 * - Port L: Yellow/green LEDs (upper nibble output)
 *
 * Push button reads support active-low and active-high logic depending on
 * the hardware configuration.
 *
 * MECH 458, Fall 2026, Khephren Gould & Clifton Tollefson
 */

#ifndef BREADBOARDIO_H
#define BREADBOARDIO_H
#include "avr/io.h"

// DC MOTOR
#define INA (1 << PB0)
#define INB (1 << PB1)
#define ENA (1 << PB2)
#define ENB (1 << PB3)
// STEPPER MOTOR
#define EN0_PIN (1 << PA0)
#define L1_PIN (1 << PA1)
#define L2_PIN (1 << PA2)
#define EN1_PIN (1 << PA3)
#define L3_PIN (1 << PA4)
#define L4_PIN (1 << PA5)
// HE SENSOR
#define HE (1 << PF1)
// OR SENSOR
#define OR (1 << PD2)
// push buttons
#define PAUSE (1 << PD0)
#define RAMP_DOWN (1 << PD1)
// yg leds
#define YG_LEDS (0xF << PL4)

typedef enum
{
    ACTIVE_LOW = 0,
    ACTIVE_HIGH = 1
} PB_POLARITY_t;

/* init_breadboard_io
 * Configures the breadboard I/O pins by setting the data direction registers.
 *
 * Port A: Configured as output for stepper motor control.
 * Port B: Configured as output for DC motor control.
 * Port C: Configured as output for red LEDs and LCD interface.
 * Port D: Configured as input for push buttons and optical sensor.
 * Port F: Configured as input for ADC and HE sensor.
 * Port L: Upper nibble configured as output for yellow/green LEDs.
 */
void init_breadboard_io();

/* write_red_leds
 * Writes an 8-bit value to the red LED bank connected to Port C.
 *
 * value: Bit pattern corresponding to the desired LED states.
 *        Each bit controls one red LED.
 */
void write_red_leds(uint8_t value);

/* write_yg_leds
 * Writes a 4-bit value to the yellow/green LED bank connected to Port L.
 * The lower four bits of value are shifted into the upper nibble of PORTL.
 * Other bits of PORTL are preserved.
 *
 * value: 4-bit LED pattern (0x0-0xF).
 */
void write_yg_leds(uint8_t value);

/* read_switches
 * Reads the switch states and stores them in the provided buffer.
 *
 * buf: Pointer to the buffer in which switch states will be stored.
 */
void read_switches(uint8_t *buf);

/* read_pb1
 * Reads the state of push button 1 (PAUSE) connected to PD0.
 *
 * polarity: ACTIVE_HIGH returns 1 when the pin is high.
 *           ACTIVE_LOW returns 1 when the pin is low.
 *
 * Returns 1 if the button is active and 0 otherwise.
 */
uint8_t read_pb1(PB_POLARITY_t polarity);

/* read_pb2
 * Reads the state of push button 2 (RAMP_DOWN) connected to PD1.
 *
 * polarity: ACTIVE_HIGH returns 1 when the pin is high.
 *           ACTIVE_LOW returns 1 when the pin is low.
 *
 * Returns 1 if the button is active and 0 otherwise.
 */
uint8_t read_pb2(PB_POLARITY_t polarity);

#endif