/*
 * dcmotor.c
 *
 * Created: 10/26/2026 10:27:03 PM
 *  Author: cliftontollefson
 */ 
#include "avr/io.h"
#include "avr/interrupt.h"
#include "dcmotor.h"


//Function that turns the DC motor counter clockwise, turning the conveyor forwards
void forward(){
	PORTB = (INB | ENA | ENB);
}

//function that turns DC motor clockwise, turning the conveyor backwards
void reverse(){
	PORTB = (INA | ENA | ENB);
}

//Function stops the DC motor
void break_hi(){
	PORTB = (INA | INB | ENA | ENB);
}
