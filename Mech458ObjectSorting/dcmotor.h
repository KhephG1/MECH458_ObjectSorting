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

#define DUTY_50_PERCENT (128)
#define PRESCALER_3kHZ (8)

void forward();
void reverse();
void break_hi();
void set_direction_flag();
void clear_direction_flag();
uint8_t is_direction_flag();
void init_dcmotor(uint8_t duty_cycle_counts, uint16_t prescaler);
#endif /* DCMOTOR_H_ */
