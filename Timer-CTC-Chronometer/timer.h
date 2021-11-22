/*
 * Date: 22/11/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdint.h>

uint8_t timer_ctc(uint8_t n, uint16_t compare, uint8_t prescaler);
