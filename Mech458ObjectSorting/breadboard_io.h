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

void init_breadboard_io();

void write_red_leds(uint8_t value);
void write_yg_leds(uint8_t value);
void read_switches(uint8_t *buf);
uint8_t read_pb1(PB_POLARITY_t polarity);
uint8_t read_pb2(PB_POLARITY_t polarity);

#endif