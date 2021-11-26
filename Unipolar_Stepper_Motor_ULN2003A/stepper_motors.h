/*
 * Date: 25/11/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define CLOCK_WISE  0 // Clock Wise
#define CCLOCK_WISE 1 // Counter Clock Wise

#include <stdint.h>

void step_align(void);
void uni_full_step(uint16_t steps, int8_t *current_step, uint8_t direction);
void uni_half_step(uint16_t half_steps, int8_t *current_step, uint8_t direction);