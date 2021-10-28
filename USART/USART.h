/*
 * Date: 27/10/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

/**************************************
 * Register Description:
 * ----------------------
 * [UBRRn[H;L]]: Set the baud rate
 *               (USART Baud Rate Register)
 * [UCSRnA]: - Used to check if the data transmition buffer is empty (UDRE bit)
 *           - Used to check if there is unread data in the receive buffer (RXC)
 *           - Used to enable double speed mode (U2X)
 *             (USART Control and Status Register)
 * [UCSRnB]: - Used to enable the receiver, transmitter, and their interrupts
 *             (TXEN, RXEN, RXCIE, TXCIE)
 *             (USART Control and Status Register)
 * [UCSR0C]: - Used to determine USART operation momde (UMSEL[1:0])
 *           - Used for setting the number of stop bits
 *           - Used for setting the number of data bits
 *           - Used for setting the parity state
 *             (USART Control and Status Register)
 * [UDRn]:   - The transmission and reception buffer
 *             (USART Data Register)
 * [DDRx]:   - Used to determine if master or slave in synchronous mode
 *             (Data Direction Register)
 **************************************/

#ifndef USART_H_
#define USART_H_

#include <stdint.h>

#define BAUD 9600UL // Baud rate

/* Samples per-bit:
 * SYNC: 16 for normal speed mode, and 8 for double speed mode
 * ASYNC: Always 2*/
#define SAMPLE_RATE_SYNC  2UL
#define SAMPLE_RATE_ASYNC 8UL

// Corresponding UBRR value
#define UBRR_SYNC  (F_CPU / (BAUD * SAMPLE_RATE_SYNC)) - 1
#define UBRR_ASYNC (F_CPU / (BAUD * SAMPLE_RATE_ASYNC)) - 1

// To be passed as argument with "USART_asynch_init" function in "speed" parameter
#define DOUBLE_SPEED 1
#define NORMAL_SPEED 0

// To be passed as argument with "USART_synch_init" function in "role" parameter
#define MASTER 1
#define SLAVE  0

extern uint8_t parity_error;
extern uint8_t frame_error;

int USART_asynch_init(uint8_t port, volatile uint16_t ubrr, uint8_t speed);
int USART_synch_init(uint8_t port, volatile uint16_t ubrr, uint8_t role);
int USART_putchar(uint8_t port, volatile char data);
int USART_putstr(uint8_t port, const char *string);
int USART_putint(uint8_t port, int16_t value, uint8_t arr_size, uint8_t base);
int USART_putlongint(uint8_t port, int32_t value, uint8_t arr_size);
int USART_putdouble(uint8_t port, double value, uint8_t arr_size, uint8_t width, uint8_t prec);
char USART_getchar(uint8_t port);
#endif