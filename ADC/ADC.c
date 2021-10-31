/*
 * Date: 27/10/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/iom324pb.h>

/* Initialize ADC peripheral with the fllowing settings
 * Prescaler = 128 for frequency in [50kHz:200kHz] for max accuracy
 * No interrupt
 * No auto-trigerring
 */
void ADC_init(void)
{
    ADCSRA = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADEN);
}

/* Get conversion value of the ADC from the indicated channel
 * CHANNEL: ADC channel to read [0:7]
 * RETURN: Value of the ADC conversion on succes, -1 on channel number/mode failure
 */
int16_t ADC_get(uint8_t channel)
{
    if (channel > 0x1F) // Verify that a single input ended mode is chosen
        return -1;
    ADMUX = channel;                // Indicate the channel in single ended input mode
    ADCSRA |= (1 << ADSC);          // Start a conversion
    while (!(ADCSRA & (1 << ADIF))) // Wait until the "conversion complete" flag is set
        ;
    return ADCL | (ADCH << 8);
}