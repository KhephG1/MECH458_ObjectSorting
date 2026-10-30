#ifndef BREADBOARDIO_H
#define BREADBOARDIO_H

#include "avr/io.h"
#define RED_LEDS_PORT (PORTC)
#define YG_LEDS_PORT (PORTL)
#define PUSH_BUTTON1_PORT (PINA)
#define PUSH_BUTTON2_PORT (PINA)
#define SLIDE_SWITCH_PORT (PINA)

typedef enum
{
    ACTIVE_LOW = 0,
    ACTIVE_HIGH = 1
} PB_POLARITY_t;

void init_breadboard_io();

void write_red_leds(uint8_t value);
void write_yg_leds(uint8_t value);
void read_switches(uint8_t *buf);
uint8_t read_pb1(PB_POLARITY_t polarity);
uint8_t read_pb2(PB_POLARITY_t polarity);

#endif