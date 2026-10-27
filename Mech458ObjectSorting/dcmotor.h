/*
 * dcmotor.h
 *
 * Created: 10/26/2026 10:29:11 PM
 *  Author: cliftontollefson
 */ 


#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "mtimer.h"

#define INA (1 << PB0)
#define INB (1 << PB1)
#define ENA (1 << PB2)
#define ENB (1 << PB3)

DDRB = 0xFF;	//sets direction of port B to output

void forward();
void reverse();
void break_hi();


#endif /* DCMOTOR_H_ */