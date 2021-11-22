/*
 * Date: 22/11/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/iom324pb.h>
#include <stdint.h>

/********************************
 * CTC mode timer used as chronometer (interrupt on output compare match)
 * n: 16-bit timer number (1, 3, or 4)
 * compare: 16-bit unsigned value of output compare register
 * prescaler: prescaler of timer clock, 8 possible values (0 to 7)
 * Return: 0 on success;
 *         1 on wrong unvalid prescaler value
 *         2 on unvalid compare output register value
 *         3 on unvalid timer number
 ********************************/
uint8_t timer_ctc(uint8_t n, uint16_t compare, uint8_t prescaler)
{
    if (prescaler > 7)
        return 1;
    if ((compare > 65535) || (compare < 0))
        return 2;
    switch (n)
    {
        case 1:
            TCCR1B = prescaler | (1 << WGM12); // Set prescaler and CTC mode
            // Number of ticks to compare with counter TCNTn (Timers TOP)
            OCR1AH = (compare >> 8);
            OCR1AL = (compare & 0xFF);
            TIMSK1 = (1 << OCIE1A); // Output compare match interrupt enable
            return 0;
        case 3:
            TCCR3B = prescaler | (1 << WGM32); // Set prescaler and CTC mode
            // Number of ticks to compare with counter TCNTn (Timers TOP)
            OCR3AH = (compare >> 8);
            OCR3AL = (compare & 0xFF);
            TIMSK3 = (1 << OCIE3A); // Output compare match interrupt enable
            return 0;
        case 4:
            TCCR4B = prescaler | (1 << WGM42); // Set prescaler and CTC mode
            // Number of ticks to compare with counter TCNTn (Timers TOP)
            OCR4AH = (compare >> 8);
            OCR4AL = (compare & 0xFF);
            TIMSK4 = (1 << OCIE4A); // Output compare match interrupt enable
            return 0;
        default:
            return 3;
    }
}