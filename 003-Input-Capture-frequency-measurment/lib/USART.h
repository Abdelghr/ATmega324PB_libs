/*
 * Date: 27/10/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

#ifndef USART_H_
#define USART_H_

#include <stdint.h>

#define BAUD 9600UL // Baud rate

/* Samples per-bit:
 * ASYNC: 16 for normal speed mode, and 8 for double speed mode
 * SYNC: Always 2*/
#define SAMPLE_RATE_SYNC  2UL
#define SAMPLE_RATE_ASYNC 16UL

// Corresponding UBRR value
#define UBRR_SYNC  (F_CPU / (BAUD * SAMPLE_RATE_SYNC)) - 1
#define UBRR_ASYNC (F_CPU / (BAUD * SAMPLE_RATE_ASYNC)) - 1

// To be passed as argument with "USART_synch_init" function in "role" parameter
#define MASTER 1
#define SLAVE  0

extern uint8_t parity_error;
extern uint8_t frame_error;

int USART_asynch_init(uint8_t port, volatile uint16_t ubrr);
int USART_synch_init(uint8_t port, volatile uint16_t ubrr, uint8_t role);
int USART_putchar(uint8_t port, volatile char data);
int USART_putstr(uint8_t port, const char *string);
int USART_putint(uint8_t port, int16_t value, uint8_t arr_size, uint8_t base);
int USART_putlongint(uint8_t port, int32_t value, uint8_t arr_size);
int USART_putdouble(uint8_t port, double value, uint8_t arr_size, uint8_t width, uint8_t prec);
char USART_getchar(uint8_t port);
#endif