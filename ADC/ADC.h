/*
 * Date: 27/10/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

/**************************************
 * Register Description
 * ------------------------
 * [ADCSRA]:   - Enabling the ADC
 *             - Setting prescaler for a frequency allowing for maximum resolution
 *               [50kHz:200kHz]
 *               (ADC Control and Status Register A)
 * [ADCSRB]:   - Leaving autotrigger source as default (not used)
 *             - Leaving analog comparator multiplexer unused
 *               (ADC Control and Status Register B)
 * [ADMUX]:    - Selecting channel and mode of operation
 *             - Leaving data registers right adjusted
 *             - Leaving voltage reference as external AREF pin
 *               (ADC Multiplexer Selection Register)
 * [ADC[L;H]]: - Fetching the ADC conversion results
 *               (ADC Data Conversion Registers [Low and High])
 *************************************/

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void ADC_init(void);
int16_t ADC_get(uint8_t channel);

#endif