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
