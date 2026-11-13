/*
 * dcmotor.h
 *
 * Created: 10/26/2026 10:29:11 PM
 *  Author: cliftontollefson
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "mtimer.h"
#include <stdint.h>

void forward();
void reverse();
void break_hi();
void set_direction_flag();
void clear_direction_flag();
uint8_t is_direction_flag();

#endif /* DCMOTOR_H_ */
