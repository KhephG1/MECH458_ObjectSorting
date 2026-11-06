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
#include "dcmotor.h"
#include "lcd.h"
#include "mtimer.h"
#include "pwm.h"
#include <avr/interrupt.h>
#include <avr/io.h>
volatile uint8_t kill_switch = 0;
volatile uint8_t direction = 0;
// volatile uint8_t direction_flag = 0;
int main()
{

    // set system clock to 8MHz
    CLKPR = _BV(CLKPCE);
    CLKPR = _BV(CLKPS0);
    // Configure I/O and interrupts
    cli();
    // config the external interrupt ======================================
    EIMSK |= (_BV(INT2));               // enable INT2 for direction switch
    EICRA |= (_BV(ISC21) | _BV(ISC20)); // rising edge interrupt

    EIMSK |= (_BV(INT3)); // enable INT3 for kill switch
    EICRA |= _BV(ISC31);  // falling edge interrupt

    init_TIM0();
    init_pwm(127, 64);
    init_dc_motor();
    init_breadboard_io();
    init_adc(ONE_SHOT, AVCC, ADC_IRQ_ENABLE, ADC_8_BITS);
    // Initialize LCD module
    InitLCD(LS_BLINK | LS_ULINE);
    LCDClear();
    // ALL I/O and Interrupts configured
    sei();

    while (1)
    {
        int16_t result = read_adc();

        mTimer(50);
        if (result != -1)
        {

            LCDWriteIntXY(0, 0, result, 3);
            set_duty_cycle(result);
        }
        // do pwm stuff

        if (kill_switch == 1)
        {

            LCDWriteStringXY(0, 0, "Kill Switch");
            break_hi();
            while (1)
            {
                // do nothing, we are in break state
                // write_red_leds(0xFF);
                write_yg_leds(15);
            }
        } // kill switch
        if (is_direction_flag())
        {
            LCDWriteStringXY(0, 1, "Flag set");
            clear_direction_flag();
            break_hi();
            if (direction == 0)
            {

                forward();
                LCDClear();
                LCDWriteStringXY(0, 1, "fwd");
                write_yg_leds(12);
            }
            else
            {
                reverse();
                LCDClear();
                LCDWriteStringXY(0, 1, "back");
                write_yg_leds(3);
            }
            // direction_flag = 0;
        }
    }
    return 0;
} // end main

ISR(INT2_vect)
{
    write_yg_leds(16);
    set_direction_flag();
    break_hi();

    if (direction == 0)
    {
        direction = 1;
    }
    else
    {
        direction = 0;
    }
}

ISR(INT3_vect) { kill_switch = 1; }
