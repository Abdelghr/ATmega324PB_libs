/*
 * Date: 23/11/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdint.h>

uint8_t pwm_servo(uint8_t n, uint8_t init_pos);
uint8_t servo_pos(uint8_t n, uint8_t pos);
