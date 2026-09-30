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
enum direction {LEFT, RIGHT};
int main(void) {
    /* Replace with your application code */
	msysInit();
	mtimerInit();
	mgpioInit();
	sei(); // enable interrupts (on the processor side)
	mstartTimerAutoReload(KNIGHTRIDER_PERIOD);
	uint16_t pattern = 0x03;
	enum direction dir = LEFT;
    while (1) { 
		if(tim3_exp){
			tim3_exp = 0;
			//shift the two bit knightrider pattern
			if(dir == LEFT){
				if(pattern > 0xC0){
					dir = RIGHT;
					pattern >>= 1;
				}else{
					pattern <<= 1;
				}
			} else { // dir = RIGHT
				if(pattern == 0x01){
					dir = LEFT;
					pattern = 3;
				}else{
					pattern >>= 1;
				}
			}
			PORTC = pattern;
			
		}
    }
}

