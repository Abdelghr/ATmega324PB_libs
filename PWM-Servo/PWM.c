/*
 * Date: 23/11/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

/********************************
 * Timer used in fast PWM mode (14), for generation of a PWM signal for a servo
 * motor (Servo Motor SG90). ICRn defines the TOP (signal period) and OCR1A the
 * output compare value defines the duty cycle.
 ********************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/iom324pb.h>
#include <stdint.h>

/*********************************
 * Non-inverted PWM signal for a servo motor
 * n: 16-bit timer number (1, 3, or 4)
 * init_pos: Position of a the servo between 0° and 180°
 * Return: 0 on success;
 *         1 on invalid servo position
 *         2 on invalid timer number
 ********************************/
uint8_t pwm_servo(uint8_t n, uint8_t init_pos)
{
    if ((init_pos > 180) || (init_pos < 0))
        return 1;
    // Calculate output register value for wanted servo position
    uint16_t dc = init_pos * 11.11 + 1999;
    switch (n)
    {
        case 1:
            DDRD = (1 << DDD5); // PWM pin as output
            // Fast PWM mode 14, TOP = ICRn, Output = OCnA, prescaler = 8
            TCCR1A = (1 << WGM11) | (1 << COM1A1);
            TCCR1B = (1 << CS11) | (1 << WGM12) | (1 << WGM13);
            // Define TOP for 20ms signal period
            ICR1H = (40000 >> 8);
            ICR1L = (40000 & 0xFF);
            // Duty cycle
            OCR1AH = (dc >> 8);
            OCR1AL = (dc & 0xFF);
            return 0;
        case 3:
            // CAUTION: Same pin used for ICSP
            DDRB = (1 << DDB6); // PWM pin as output
            // Fast PWM mode 14, TOP = ICRn, Output = OCnA, prescaler = 8
            TCCR3A = (1 << WGM31) | (1 << COM3A1);
            TCCR3B = (1 << CS31) | (1 << WGM32) | (1 << WGM33);
            // Define TOP for 20ms signal period
            ICR3H = (40000 >> 8);
            ICR3L = (40000 & 0xFF);
            // Duty cycle
            OCR3AH = (dc >> 8);
            OCR3AL = (dc & 0xFF);
            return 0;
        case 4:
            DDRC = (1 << DDC4); // PWM pin as output
            // Fast PWM mode 14, TOP = ICRn, Output = OCnA, prescaler = 8
            TCCR4A = (1 << WGM41) | (1 << COM4A1);
            TCCR4B = (1 << CS41) | (1 << WGM42) | (1 << WGM43);
            // Define TOP for 20ms signal period
            ICR4H = (40000 >> 8);
            ICR4L = (40000 & 0xFF);
            // Duty cycle
            OCR4AH = (dc >> 8);
            OCR4AL = (dc & 0xFF);
            return 0;
        default:
            return 3;
    }
}

/*********************************
 * Modifies PWM duty cycle for new servo position
 * n: 16-bit timer number (1, 3, or 4)
 * pos: Position of a the servo between 0° and 180°
 * Return: 0 on success;
 *         1 on invalid servo position
 *         2 on invalid timer number
 ********************************/
uint8_t servo_pos(uint8_t n, uint8_t pos)
{
    if ((pos > 180) || (pos < 0))
        return 1;
    uint16_t dc = pos * 11.11 + 1999;
    switch (n)
    {
        case 1:
            OCR1AH = (dc >> 8);
            OCR1AL = (dc & 0xFF);
            return 0;
            break;
        case 3:
            OCR3AH = (dc >> 8);
            OCR3AL = (dc & 0xFF);
            return 0;
            break;
        case 4:
            OCR4AH = (dc >> 8);
            OCR4AL = (dc & 0xFF);
            return 0;
            break;
        default:
            return 2;
    }
}