/*
 * Date: 25/11/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/iom324pb.h>
#include <util/delay.h>

/***************************************
 * Aligns the stepper motor with a phase
 ***************************************/
void step_align(void)
{
    PORTC = (PORTC & 0b11110000) | 0b00000001;
    _delay_ms(1000);
}

/***************************************
 * Turns the stepper motor by the indicated number of steps
 * steps: The number of steps by which to turn the motor
 * current_step: The current step in the step sequences
 *      - After alignment, in the first use of this function, current_step = 1
 * Direction: Turning direction, clock wise or counter clock wise
 *      - 0: Counter clock wise
 *      - non-zero: Clock wise
 ***************************************/
void uni_full_step(uint16_t steps, int8_t *current_step, uint8_t direction)
{
    if (direction) // If truning counter clock wise
        while (steps)
        {
            if (*current_step == 3)
                *current_step = 0;
            else
                (*current_step)++;
            PORTC = (PORTC & 0b11110000) | (1 << *current_step);
            steps--;
            _delay_ms(100);
        }
    else // If turning clock wise
        while (steps)
        {
            if (*current_step == 0)
                *current_step = 3;
            else
                (*current_step)--;
            PORTC = (PORTC & 0b11110000) | (1 << *current_step);
            steps--;
            _delay_ms(100);
        }
}

/***************************************
 * Turns the stepper motor by the indicated number of half_steps
 * hald_steps: The number of half_steps by which to turn the motor
 * current_step: The current step in the step sequences
 *      - After alignment, in the first use of this function, current_step = 1
 * Direction: Turning direction, clock wise or counter clock wise
 *      - 0: Counter clock wise
 *      - non-zero: Clock wise
 ***************************************/
void uni_half_step(uint16_t half_steps, int8_t *current_step, uint8_t direction)
{
    uint8_t step_seq[8] = {
        0b00000001,
        0b00000011,
        0b00000010,
        0b00000110,
        0b00000100,
        0b00001100,
        0b00001000,
        0b00001001,
    };
    if (direction) // If truning counter clock wise
        while (half_steps)
        {
            if (*current_step == 7)
                *current_step = 0;
            else
                (*current_step)++;
            PORTC = (PORTC & 0b11110000) | *(step_seq + *current_step);
            half_steps--;
            _delay_ms(100);
        }
    else // If turning clock wise
        while (half_steps)
        {
            if (*current_step == 0)
                *current_step = 7;
            else
                (*current_step)--;
            PORTC = (PORTC & 0b11110000) | *(step_seq + *current_step);
            half_steps--;
            _delay_ms(100);
        }
}