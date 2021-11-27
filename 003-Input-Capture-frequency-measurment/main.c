/*
 * Date: 27/11/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define T_UNIT_VAL        4096 // Number of micro seconds in one time unit
#define NUMBER_OF_SAMPLES 5    // Number of period samples used to calculate the frequency
#define LOST_CYCLES       66   // Clock cycles not accounted for between samples

#include "lib/USART.h"
#include "lib/timer.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom324pb.h>

volatile uint32_t time_unit; // 1 time_unit = 4096 micro seconds
double samples[NUMBER_OF_SAMPLES + 1];
uint8_t sample_inedx;
double freq;

double calc_freq(const double *);

ISR(TIMER1_OVF_vect)
{
    time_unit++;
}

ISR(TIMER1_CAPT_vect)
{
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    uint8_t temp;
    temp = ICR1L;
    samples[sample_inedx++] = time_unit * T_UNIT_VAL + ((temp | (ICR1H << 8)) + LOST_CYCLES) * 0.0625;
    time_unit = 0;
    if (sample_inedx == NUMBER_OF_SAMPLES + 1)
    {
        cli();
        freq = calc_freq(samples);
        USART_putdouble(0, freq, 18, 8, 8);
        USART_putchar(0, '\r');
        sample_inedx = 0;
    }
}

int main()
{
    sei();
    USART_asynch_init(0, UBRR_ASYNC);
    timer(1);

    while (1)
    {
    }
    return 0;
}

double calc_freq(const double *samples)
{
    double period = 0;
    for (uint8_t i = 1; i < 6; i++)
    {
        period += *(samples + i);
    }
    period /= 5;
    return 1 / period;
}