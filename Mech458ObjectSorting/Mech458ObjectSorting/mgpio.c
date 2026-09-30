/*
 * _gpio.c
 *
 * Created: 2026-09-30 11:56:26 AM
 *  Author: Kheph
 */ 
#include <avr/io.h>
#include "mgpio.h"
void mgpioInit(void){
	DDRL = 0xFF; // Sets all pins on PORTL to output
	PORTL = 0xF0; // initialize pins to high to turn on LEDs (2 Yel & 2 Grn)
	DDRC = 0xFF; // initialize port C pins to output
	PORTC = 0xFF; //initialize pins to high to turn on LEDs (8 Red)
}