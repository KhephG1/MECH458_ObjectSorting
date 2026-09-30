/*
 * timer.h
 *
 * Created: 2026-09-30 11:13:38 AM
 *  Author: Kheph
 */ 


#ifndef TIMER_H_
#define TIMER_H_
//these flags are set when the oneshot / autoreload timer interrupts fire
extern volatile uint8_t tim3_exp;
extern volatile uint8_t tim4_exp;
void mtimerMillis(int millis);

void mstartTimerAutoReload(uint16_t period_millis);

void mstartTimerOneShot(uint16_t millis);

void mtimerInit(void);




#endif /* TIMER_H_ */