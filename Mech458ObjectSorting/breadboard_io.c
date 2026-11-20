/* breadboard_io.c
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
#include "breadboard_io.h"
void init_breadboard_io()
{
    // port C used for Red LEDs & LCD (output)
    DDRC = 0xFF;
    // port L used for YG LEDs
    DDRL = 0xF0;
    // port A used for stepper controls (output)
    DDRA = 0xFF;
    // Port D pins used as interrupts (input)
    DDRD = 0x00;
    // Port B pins used for DC motor outputs
    // Port B Pin 7 is the dc motor pwm signal
    DDRB = 0xFF;
    // Port F used for ADC (PF0) and HE sensor (PF1)
    DDRF = 0x00;
}

void write_red_leds(uint8_t value) { PORTC = value; }
void write_yg_leds(uint8_t value) { PORTL = PORTL & ~(YG_LEDS) | (value << 4); }
uint8_t read_pb1(PB_POLARITY_t polarity)
{
    return polarity ? !!(PIND & PAUSE) : !(PIND & PAUSE);
}
uint8_t read_pb2(PB_POLARITY_t polarity)
{
    return polarity ? !!(PIND & RAMP_DOWN) : !(PIND & RAMP_DOWN);
}
