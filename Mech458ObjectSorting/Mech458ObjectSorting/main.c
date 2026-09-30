/*
 * Mech458ObjectSorting.c
 *
 * Created: 2026-09-30 10:24:03 AM
 * Author : Kheph
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "mtimer.h"
#include "mgpio.h"

#define KNIGHTRIDER_PERIOD (50)
void msysInit(void){
	CLKPR = _BV(CLKPCE);
	CLKPR = _BV(CLKPS0);
}
int main(void) {
	msysInit();
	TCCR1B |= _BV(CS11);
	DDRL = 0xFF; // Sets all pins on PORTL to output
	PORTL = 0xF0; // initialize pins to high to turn on LEDs (2 Yel & 2 Grn)
	DDRC = 0xFF; // initialize port C pins to output
	mTimer(KNIGHTRIDER_PERIOD);
	while(1){
		PORTC = 0b11000000;
		mTimer(KNIGHTRIDER_PERIOD);
	 	PORTC = 0b11100000;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b11110000;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b01111000;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00111100;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00011110;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00001111;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00000111;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00000011;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00000111;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00001111;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00011110;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00111100;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b01111000;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b11110000;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b11100000;
		mTimer(KNIGHTRIDER_PERIOD);

	}	

	return (0); 
	
}

