#ifndef PWM_H
#define PWM_H

#define CW 1
#define CCW 0

// Bit masks for PORTA
#define EN0_PIN (1 << PA0)
#define L1_PIN (1 << PA1)
#define L2_PIN (1 << PA2)
#define EN1_PIN (1 << PA3)
#define L3_PIN (1 << PA4)
#define L4_PIN (1 << PA5)

void init_TIM0();
void init_pwm(uint8_t duty_cycle_counts, uint16_t prescaler);
uint8_t rotate(uint8_t dir, uint8_t steps, uint8_t current_step);
void set_duty_cycle(uint8_t duty_cycle_counts);

#endif