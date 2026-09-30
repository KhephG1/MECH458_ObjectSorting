/*
 * _timer.c
 *
 * Created: 2026-09-30 11:17:58 AM
 *  Author: Kheph
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include "mtimer.h"
//on avr you can use the ISR macro to assign a handler for your interrupts
//you give the macro the vector that you would like your ISR to be triggered for


//oneshot timer
volatile uint8_t tim4_exp = 0;
ISR(TIMER4_COMPA_vect){
	tim4_exp = 1;
}


//autoreload timer
volatile uint8_t tim3_exp = 0;
ISR(TIMER3_COMPA_vect){
 //set tim_3_exp flag to 1	
	tim3_exp = 1;
}

static inline uint16_t ms_to_ocr(uint16_t ms)
{
	if (ms > 8191) ms = 8191;
	if (ms == 0) ms = 1;
	return (ms << 3) - 1;
}

void mtimerInit(void){
	//sets timer to run at 1MHz
	TCCR1B |= _BV(CS11);
	//ensure tim2(one shot) is stopped
	TCCR4B = 0; 
	//ensure tim3(autoreload) is stopped
	TCCR3B = 0;
}
//an asynchronous one shot timer using the TIM2 peripheral
//IMPORTANT: Max time is 8.19 seconds (with 8Mhz system clock)
void mstartTimerOneShot(uint16_t millis){
	uint16_t counts = ms_to_ocr(millis);
	//enable output compare interrupts 
	TIMSK4 |= _BV(OCIE4A);
	//set the output compare register to the desired counts
	OCR4A = counts;
	//clear any stale OCR interrupt flags
	TIFR4 = _BV(OCF4A);
	//ensure timer starts at 0
	TCNT4 = 0x0000;
	//start the timer with 1024 prescaler
	TCCR4B = _BV(WGM42) | _BV(CS42) | _BV(CS40);
}
//an asynchronous autoreload timer using the TIM3 peripheral
//IMPORTANT: Max time is 8.19 seconds (with 8Mhz system clock)
void mstartTimerAutoReload(uint16_t period_millis){
	uint16_t counts = ms_to_ocr(period_millis);
	//configure timer for autoreload mode
	TCCR3B |= _BV(WGM12);
	//enable output compare interrupts
	TIMSK3 |= _BV(OCIE3A);
	//set the output compare register to the desired counts
	OCR3A = counts;
	//clear any stale OCR interrupts
	TIFR3 = _BV(OCF3A);
	//ensure timer starts at 0
	TCNT3 = 0x0000;
	//start the timer with 1024 prescaler
	TCCR3B = _BV(WGM32) | _BV(CS32) | _BV(CS30);	
}

//A blocking timer implementation that uses the TIM1 peripheral
void mTimer(uint16_t count){
	 uint16_t i = 0;
	//automatically clears count after OCR1A is reached 
	TCCR1B |= _BV(WGM12);
	//
	OCR1A = 0x03EB;
	TCNT1 = 0x0000;
	TIMSK1 |= 0x02;
	TIFR1 = _BV(OCF1A);
	while(i < count){
		if((TIFR1 & 0x02) == 0x02){
			TIFR1 = _BV(OCF1A);
			i++;
		}
	}
	return;	
}
