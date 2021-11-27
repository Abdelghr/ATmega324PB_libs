/*
 * Date: 27/11/2021
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
 * Timer in normal mode, measuring frequency of periodic event
 * n: 16-bit timer number (1, 3, or 4)
 * Return: 0 on success;
 *         1 on invalid timer number
 ********************************/
uint8_t timer(uint8_t n)
{
    switch (n)
    {
        case 1:
            // Set prescaler, leave in normal mode, activate noise canceler and
            // rising edge trigger for input capture
            TCCR1B = (1 << CS10) | (1 << ICNC1) | (1 << ICES1);
            // Activate input capture and overflow interrupts
            TIMSK1 = (1 << ICIE1) | (1 << TOIE1);
            // Output compare register set to go off at same time as overflow
            return 0;
        case 3:
            // Set prescaler, leave in normal mode, activate noise canceler and
            // rising edge trigger for input capture
            TCCR3B = (1 << CS30) | (1 << ICNC3) | (1 << ICES3);
            // Activate input capture and overflow interrupts
            TIMSK3 = (1 << ICIE3) | (1 << TOIE3);
            return 0;
        case 4:
            // Set prescaler, leave in normal mode, activate noise canceler and
            // rising edge trigger for input capture
            TCCR4B = (1 << CS40) | (1 << ICNC4) | (1 << ICES4);
            // Activate input capture and overflow interrupts
            TIMSK4 = (1 << ICIE4) | (1 << TOIE4);
            return 0;
        default:
            return 1;
    }
}