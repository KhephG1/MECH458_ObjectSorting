
/*
 * Lab4bADC.c
 *
 * Created: 2026-10-22 10:20:38 PM
 *  Author: Kheph
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>
#include "pwm.h"
#include "mtimer.h"
// define the global variables that can be used in every function ==========
volatile unsigned char ADC_result;
volatile unsigned int ADC_result_flag;
volatile uint8_t direction = 0;
volatile uint8_t direction_flag = 0;
#define PRESCALER_488HZ (64)
#define BREAK (0x0F)
#define DUTY_CYCLE_MAX (255)

void msysInit(void){
	//set system clock to 8MHz
	CLKPR = _BV(CLKPCE);
	CLKPR = _BV(CLKPS0);
}

int main()
{
	msysInit();
	cli(); // disable all of the interrupt ==========================
	// config the external interrupt ======================================
	EIMSK |= (_BV(INT2)); // enable INT2
	EICRA |= (_BV(ISC21) | _BV(ISC20)); // rising edge interrupt
	// config ADC =========================================================
	// by default, the ADC input (analog input is set to be ADC0 / PORTF0
	ADCSRA |= _BV(ADEN); // enable ADC
	ADCSRA |= _BV(ADIE); // enable interrupt of ADC
	ADMUX |= _BV(ADLAR) | _BV(REFS0); // ADLAR left justifies the ADC data, Selects ADC 0 as Channel, use AVCC (5v) as ref
	ADCSRA |= _BV(ADATE);
	ADCSRA |= _BV(ADSC);
	// set the PORTC as output to display the ADC result ==================
	DDRC = 0xff;
	DDRB = 0x0f;
	// sets the Global Enable for all interrupts ==========================
	sei();
	PORTB = 0x07;
	init_TIM0();
	init_pwm(127,PRESCALER_488HZ);
	//mTimer(500);
	while (1)
	{ 
		if (ADC_result_flag)
		{
			PORTC = ADC_result;
			ADC_result_flag = 0x00;
			set_duty_cycle(ADC_result);
		}
		if(direction_flag){
			if(direction){
				PORTB = 0x07;
			}else{
				PORTB = 0x0B;
			}
			direction_flag = 0;	
		}	
	}
	return 0;
} // end main
// sensor switch: Active HIGH starts AD converstion =======
ISR(INT2_vect)
{ // when there is a rising edge, we need to do ADC =====================
	direction = !direction;
	mTimer(5);
	set_duty_cycle(60);
	PORTB = BREAK;
	direction_flag = 1;
}

// the interrupt will be trigured if the ADC is done ========================
ISR(ADC_vect)
{
	ADC_result = ADCH;
	ADC_result_flag = 1;
}
