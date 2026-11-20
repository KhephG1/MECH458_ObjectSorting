/* adc.h
 * ADC driver for the ATmega328P
 * - Supports 8-bit and 10-bit ADC resolution
 * - Configurable ADC reference voltage (AREF, AVCC, internal 1.1V, or 2.56V)
 * - One-shot and continuous conversion modes
 * - Optional ADC conversion-complete interrupt
 * - Converts ADC codes to voltage
 *
 * The ADC operates with a prescaler of 16 for 8-bit resolution and 64 for
 * 10-bit resolution. In continuous mode, conversions are triggered
 * automatically and the ADC ISR stores the latest result in ADC_result.
 *
 * MECH 458, Fall 2026, Khephren Gould & Clifton Tollefson
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

/* init_adc
 * Initializes the ADC with the specified conversion mode, reference voltage,
 * interrupt configuration, and resolution.
 *
 * mode: ONE_SHOT for manually triggered conversions or CONTINUOUS for
 *       automatically triggered conversions
 * vref: ADC reference voltage (AREF, AVCC, V1_1, or V2_56)
 * irq:  Enables or disables the ADC conversion-complete interrupt
 * bits: ADC_8_BITS or ADC_10_BITS
 *
 * Returns 0 on success or -1 if an invalid reference voltage is specified.
 */
int16_t init_adc(ADC_MODE_t mode, ADC_VREF_t vref, ADC_INTERRUPT_STATUS_t irq,
                 ADC_BITWIDTH_t bits);

/* read_adc
 * Reads the ADC conversion result.
 *
 * In ONE_SHOT mode, starts a conversion and blocks until it completes.
 * In CONTINUOUS mode, returns the latest conversion result if it is available,
 * otherwise returns -1. The result-available flag is cleared when read.
 *
 * Returns the ADC code (0-255 for 8-bit or 0-1023 for 10-bit resolution),
 * or -1 if no result is available in continuous mode.
 */
int16_t read_adc();

/* adc_code_to_volts
 * Converts an ADC conversion code into the corresponding input voltage.
 *
 * adc_code: ADC conversion result (0-255 for 8-bit or 0-1023 for 10-bit)
 *
 * Returns the estimated voltage at the ADC input in volts, using the
 * reference voltage configured by init_adc().
 */
float adc_code_to_volts(int16_t adc_code);

#endif