#include "stepper.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "breadboard_io.h"
#include "mtimer.h"

uint8_t stepper_step = 1;

const uint8_t portA_table[4] = {
    EN0_PIN | L1_PIN, // Step 1: EN0=1, L1=1, L2=0, EN1=0, L3=0, L4=0
    EN1_PIN | L3_PIN, // Step 2: EN0=0, L1=0, L2=0, EN1=1, L3=1, L4=0
    EN0_PIN | L2_PIN, // Step 3: EN0=1, L1=0, L2=1, EN1=0, L3=0, L4=0
    EN1_PIN | L4_PIN  // Step 4: EN0=0, L1=0, L2=0, EN1=1, L3=0, L4=1
};

uint8_t rotate(uint8_t dir, uint8_t steps, uint8_t current_step)
{
    uint8_t next_step = 0;

    while (steps > 0)
    {
        PORTA = portA_table[current_step - 1];
        switch (current_step)
        {
        case 1:
            if (dir == CW)
            {
                next_step = 2;
            }
            else
            {
                next_step = 4;
            }
            break;
        case 2:
            if (dir == CW)
            {
                next_step = 3;
            }
            else
            {
                next_step = 1;
            }
            break;
        case 3:
            if (dir == CW)
            {
                next_step = 4;
            }
            else
            {
                next_step = 2;
            }
            break;
        case 4:
            if (dir == CW)
            {
                next_step = 1;
            }
            else
            {
                next_step = 3;
            }
            break;
        default:
            break;
        } // switch
        current_step = next_step;
        steps--;
        mTimer(15);
    } // while
    return current_step;
} // rotate

int8_t home_on_black(void)
{
    // todo:
    /*
    1. check if HE sensor low
    2. if yes stop
    3. if not rotate 1 step
    4. update current step global variable
    */

    while ((PINF & HE) != 0)
    {
        stepper_step = rotate(CW, 1, stepper_step);
    }
    return 0;
}