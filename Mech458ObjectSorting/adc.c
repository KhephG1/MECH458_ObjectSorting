/*
 *adc.c
 *a library to interface with the adc on the atmega328
 */
#include "adc.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#define V_AREF (5)
uint8_t bitwidth = 0;
uint8_t adc_mode = 0;
uint8_t adc_vref = 0;
uint16_t ADC_result = 0;
uint8_t ADC_result_flag = 0;

int16_t init_adc(ADC_MODE_t mode, ADC_VREF_t vref, ADC_INTERRUPT_STATUS_t irq,
                 ADC_TRIGGER_SOURCE_t trigger, ADC_BITWIDTH_t bits)
{
    ADCSRA |= _BV(ADEN); // enable ADC
    // configure the ADC reference voltage
    switch (vref)
    {
    // AVCC (5V)
    case AVCC:
        ADMUX |= _BV(REFS0);
        break;
    // External provided reference
    case AREF:
        break;
    // internal 1.1v ref
    case V1_1:
        ADMUX |= _BV(REFS1);
        break;
    case V2_56:
        ADMUX |= _BV(REFS1) | _BV(REFS0);
        break;
    default:
        return -1;
    }
    // left justify data for 8 bits (read ADCH only)
    if (bits == ADC_8_BITS)
    {
        ADMUX |= _BV(ADLAR);
        // presclaer of 16
        ADCSRA |= BV_(ADPS2);
        bitwidth = 8;
    }
    else
    {
        bitwidth = 10;
        // prescaler of 64
        ADCSRA |= _BV(ADPS1) | _BV(ADPS2);
    }
    if (irq == ADC_IRQ_ENABLE)
    {
        ADCSRA |= _BV(ADIE); // enable interrupt of ADC
    }
    if (mode == CONTINUOUS)
    {
        ADCSRA |= _BV(ADATE);
        ADCSRA |= _BV(ADIE); // enable interrupt of ADC
        // start first conversion
        ADCSRA |= _BV(ADSC);
    }
    adc_vref = vref;
    adc_mode = mode;
    return 0;
}

int16_t read_adc(uint16_t *buffer)
{
    if (adc_mode == CONTINUOUS)
    {
        if (ADC_result_flag)
        {
            *buffer = ADC_result;
            ADC_result_flag = 0;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        // one shot
        // start conversion
        ADCSRA |= _BV(ADSC);
        while (ADCSRA & _BV(ADSC))
            ; // poll for conv complete
        if (bitwidth == 8)
        {
            *buffer = ADCH;
            return 0;
        }
        else
        {
            *buffer = ADC;
            return 0;
        }
    }
}
// a function to convert adc code (8 or 16 bits) to volts
//  takes: adc code
//  returns: voltage at adc pin in volts
//  notes: see datasheet page 280 at top for formula
float adc_code_to_volts(int16_t adc_code)
{
    switch (adc_vref)
    {
    case AVCC:
        return (adc_code * 5.0f) / 1024.0f;
        break;
    case AREF:
        return (adc_code * (float)V_AREF) / 1024.0f;
        break;
    case V1_1:
        return (adc_code * 1.1f) / 1024.0f;
        break;
    case V2_56:
        return (adc_code * 2.56f) / 1024.0f;
        break;
    default:
        break;
    }
}

ISR(ADC_vect)
{
    if (bitwidth == 8)
    {
        ADC_result = ADCH;
    }
    else
    {
        ADC_result = ADC;
    }
    ADC_result_flag = 1;
}