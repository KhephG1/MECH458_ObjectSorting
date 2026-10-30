/*
 *adc.h
 *a library to interface with the adc on the Atmega328P
 */
#ifndef ADC_H
#define ADC_H
#include "avr/io.h"
typedef enum
{
    AREF = 0,
    AVCC = 1,
    V1_1 = 2,
    V2_56 = 3,
} ADC_VREF_t;

typedef enum
{
    ADC_8_BITS = 1,
    ADC_10_BITS = 0
} ADC_BITWIDTH_t;

typedef enum
{
    ONE_SHOT = 0,
    CONTINUOUS = 1,
} ADC_MODE_t;

typedef enum
{
    ADC_IRQ_ENABLE = 1,
    ADC_IRQ_DISABLE = 0,
} ADC_INTERRUPT_STATUS_t;

float adc_code_to_volts(int16_t adc_code);
int16_t read_adc();
int16_t init_adc(ADC_MODE_t mode, ADC_VREF_t vref, ADC_INTERRUPT_STATUS_t irq,
                 ADC_BITWIDTH_t bits);

#endif