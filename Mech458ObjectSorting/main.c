// /* ##################################################################
// # MILESTONE: 5
// # PROGRAM: 1
// # PROJECT: Final Demo
// # GROUP: X
// # NAME 1: Khephren, Gould, V01012827
// # NAME 2: Clifton, Tollefson, V01004341
// # DESC: This program implements the main function for the Mech458 final
// report # DATA # REVISED
// ############################################################### *//*
#include "adc.h"
#include "breadboard_io.h"
#include "mtimer.h"
#include <avr/interrupt.h>
#include <avr/io.h>

int main()
{

    // set system clock to 8MHz
    CLKPR = _BV(CLKPCE);
    CLKPR = _BV(CLKPS0);
    // Configure I/O and interrupts
    cli();
    init_breadboard_io();
    init_adc(CONTINUOUS, AVCC, ADC_IRQ_ENABLE, ADC_FREE_RUN, ADC_8_BITS);
    uint16_t adc_val = 0;
    uint8_t switches_val = 0;
    // ALL I/O and Interrupts configured
    sei();
    while (1)
    {
        int16_t status = read_adc(&adc_val);
        if (status == 0)
        {
            write_red_leds((uint8_t)adc_val);
        }
        read_switches(&switches_val);
        write_yb_leds(switches_val);
        mTimer(500);
    }
    return 0;
} // end main
