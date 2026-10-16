#include "avr/io.h"
#include "avr/interrupt.h"
#include "pwm.h"


const uint8_t portA_table[4] = {
	EN0_PIN | L1_PIN,           // Step 1: EN0=1, L1=1, L2=0, EN1=0, L3=0, L4=0
	EN1_PIN | L3_PIN,           // Step 2: EN0=0, L1=0, L2=0, EN1=1, L3=1, L4=0
	EN0_PIN | L2_PIN,           // Step 3: EN0=1, L1=0, L2=1, EN1=0, L3=0, L4=0
	EN1_PIN | L4_PIN            // Step 4: EN0=0, L1=0, L2=0, EN1=1, L3=0, L4=1
};

void init_TIM0(){
	//put TIM0 in Fast PWM mode (Step 1)
	TCCR0A |= (_BV(WGM00) | _BV(WGM01));
	//Enable output compare A interrupt (step 2)
	TIMSK0 |= _BV(OCIE0A);
	//Clear on compare match (step 3)
	TCCR0A |= _BV(COM0A1);
	
}

void init_pwm(uint8_t duty_cycle_counts, uint16_t prescaler){
	//Set the TIM0 clock prescaler (step 4)
	// The waveform frequency is f = f(clk,io) / (N*256)
	// where fclk,io is the MCU frequency, N is the prescaler
	switch (prescaler){
		case 1024:
			TCCR0B |= _BV(CS02) | _BV(CS00);
			break;
		case 256:
			TCCR0B |= _BV(CS02);
			break;
		case 64:
			TCCR0B |= _BV(CS01);
			break;
		case 8:
			TCCR0B |= _BV(CS00);
		default:
			//in future should print error since this means f = 31.25kHz which is faster than motor supports
			break;
	}

	//set the duty cycle to 50%	(step 5)
	OCR0A = duty_cycle_counts;
	DDRB |= _BV(PB7);
}


uint8_t rotate(uint8_t dir, uint8_t steps, uint8_t current_step){
	uint8_t next_step;
	
	while (steps > 0){
		switch(current_step){
			case 1:
			PORTA |= portA_table[current_step];
			if(dir == CW){
				next_step = 2;
				}else{
				next_step = 4;
			}
			break;
			case 2:
			PORTA |= portA_table[current_step];
			if(dir == CW){
				next_step = 3;
				}else{
				next_step = 1;
			}
			break;
			case 3:
			PORTA |= portA_table[current_step];
			if(dir == CW){
				next_step = 4;
				}else{
				next_step = 2;
			}
			break;
			case 4:
			PORTA |= portA_table[current_step];
			if(dir == CW){
				next_step = 1;
				}else{
				next_step = 3;
			}
			break;
		}//switch
		current_step = next_step;
		steps--;
	}//while
	return current_step;
}//rotate