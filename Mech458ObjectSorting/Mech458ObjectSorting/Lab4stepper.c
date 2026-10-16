// /* ##################################################################
// # MILESTONE: 4
// # PROGRAM: 4
// # PROJECT: Lab4 Demo
// # GROUP: 2
// # NAME 1: Khephren, Gould, V01012827
// # NAME 2: Clifton, Tollefson, V01004341
// # DESC: This program implements the stepper motor project for Lab 4 of Mech 458
// # DATA
// # REVISED ############################################################### */
#include <stdlib.h>
#include "avr/io.h"
#include "avr/interrupt.h"
#include "mtimer.h"
#include "pwm.h"
#define DUTY_50_PERCENT (128)
#define PRESCALER_3kHZ	(8)
uint8_t current_step = 1;
int main(){
	//initalize TIM0
	init_TIM0();
	//initialize the pwm
	init_pwm(DUTY_50_PERCENT,PRESCALER_3kHZ);
	DDRA = 0xFF;
	current_step = rotate(CW,17,current_step);
	mTimer(2000);
	current_step = rotate(CW, 33,current_step);
	mTimer(2000);
	current_step = rotate(CW, 100,current_step);
	mTimer(2000);
	current_step = 4;
	current_step = rotate(CCW,17,current_step);
	mTimer(2000);
	current_step = rotate(CCW, 33,current_step);
	mTimer(2000);
	current_step = rotate(CW, 100,current_step);
	mTimer(2000);
}