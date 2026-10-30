// /* ##################################################################
// # MILESTONE: 4b
// # PROGRAM: 1
// # PROJECT: Final Demo
// # GROUP: 2
// # NAME 1: Khephren, Gould, V01012827
// # NAME 2: Clifton, Tollefson, V01004341
// # DESC: This program implements the main function for the Mech458 final
// report # DATA # REVISED
// ############################################################### *//*
#include "adc.h"
#include "breadboard_io.h"
#include "mtimer.h"
#include "dcmotor.h"
#include "pwm.h"
#include <avr/interrupt.h>
#include <avr/io.h>
volatile uint8_t kill_switch = 0;
volatile uint8_t direction = 0;


int main()
{

    // set system clock to 8MHz
    CLKPR = _BV(CLKPCE);
    CLKPR = _BV(CLKPS0);
    // Configure I/O and interrupts
    cli();
	// config the external interrupt ======================================
	EIMSK |= (_BV(INT2)); // enable INT2 for direction switch
	EICRA |= (_BV(ISC21) | _BV(ISC20)); // rising edge interrupt
	
	EIMSK |= (_BV(INT3)); // enable INT3 for kill switch
	EICRA |= _BV(ISC31); // falling edge interrupt
	
	init_TIM0();
	init_pwm(127,64);
	init_dc_motor();
    init_breadboard_io();
    init_adc(ONE_SHOT, AVCC, ADC_IRQ_ENABLE, ADC_8_BITS);
	// ALL I/O and Interrupts configured
	sei();
	
    uint8_t switches_val = 0;
	uint8_t duty_cycle = 127;
// 	forward();
// 	mTimer(2000);
// 	break_hi();
// 	mTimer(5);
// 	reverse();
// 	mTimer(2000);
// 	break_hi();
// 	mTimer(5);
	
    while (1)
    {
        int16_t result = read_adc();
        if (result != -1)
        {
			//set_duty_cycle(result);
			write_red_leds(result);
        }
        //read_switches(&switches_val);
       // write_yb_leds(switches_val);
	   
	   //do pwm stuff
		
		if(kill_switch ==1){
			break_hi();
			while(1){
				//do nothing, we are in break state
				write_red_leds(0xFF);
				write_yg_leds(15)
			}
		}//kill switch
    }
    return 0;
} // end main


ISR(INT2_vect)
{ // when there is a rising edge, we need to change direction =====================
	break_hi();
	mTimer(5);
	if(direction == 0){
		forward();
		write_yg_leds(12);
		direction = 1;
	}else{
		reverse();
		write_yg_leds(3);
		direction = 0;
	}
}


ISR(INT3_vect) 
{ // when there is a falling edge, we need to kill the motor =====================
	kill_switch = 1;
}