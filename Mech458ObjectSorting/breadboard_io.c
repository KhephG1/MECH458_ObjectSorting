#include "breadboard_io.h"
void init_breadboard_io()
{
    // all port c pins output
    DDRC = 0xFF;
    DDRL = 0xF0;
    DDRA = 0x00;
}

void write_red_leds(uint8_t value) { PORTC = value; }
void write_yg_leds(uint8_t value)
{
    YB_LEDS_PORT = YB_LEDS_PORT & ~(0xF0) | (value << 4);
}
void read_switches(uint8_t *buf) { *buf = SLIDE_SWITCH_PORT & 0x0F; }
uint8_t read_pb1(PB_POLARITY_t polarity)
{
    return polarity ? !!(PUSH_BUTTON1_PORT & 0x10)
                    : !(PUSH_BUTTON1_PORT & 0x10);
}
uint8_t read_pb2(PB_POLARITY_t polarity)
{
    return polarity ? !!(PUSH_BUTTON2_PORT & 0x20)
                    : !(PUSH_BUTTON2_PORT & 0x20);
}