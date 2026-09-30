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

#define KNIGHTRIDER_PERIOD (200)
void msysInit(void){
	CLKPR = _BV(CLKPCE);
	CLKPR = _BV(CLKPS0);
}
int main(void) {
	msysInit();
	mtimerInit();
	mgpioInit();
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

