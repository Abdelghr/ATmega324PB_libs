/*
 * Date: 27/10/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/iom324pb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Parity error bit, incremented with each parity error detection
uint8_t parity_error;
// Frame error bit, incremented with each frame error detection
uint8_t frame_error;

/* Initialize USART in asynchronous normal speed mode, 1 stop bit, Even parity,
 * no interrupts
 * PORT: USART port number
 * UBRR: UBRR register value to generate baud rate
 * RETURN: 0 on success and 1 on "port" failure
 */
int USART_asynch_init(uint8_t port, volatile uint16_t ubrr)
{
    switch (port)
    {
        case 0:
            UBRR0H = (uint8_t)(ubrr >> 8);
            UBRR0L = (uint8_t)ubrr;
            UCSR0B = (1 << TXEN) | (1 << RXEN);
            UCSR0C = (1 << UCSZ0) | (1 << UCSZ1) | (1 << UPM1);
            return 0;
        case 1:
            UBRR1H = (uint8_t)(ubrr >> 8);
            UBRR1L = (uint8_t)ubrr;
            UCSR1B = (1 << TXEN) | (1 << RXEN);
            UCSR1C = (1 << UCSZ0) | (1 << UCSZ1) | (1 << UPM1);
            return 0;
        case 2:
            UBRR2H = (uint8_t)(ubrr >> 8);
            UBRR2L = (uint8_t)ubrr;
            UCSR2B = (1 << TXEN) | (1 << RXEN);
            UCSR2C = (1 << UCSZ0) | (1 << UCSZ1) | (1 << UPM1);
            return 0;
        default:
            return 1;
    }
}

/* Initialize USART in asynchronous normal speed mode, 1 stop bit, Even parity
 * no interrupts
 * PORT: USART port number
 * UBRR: UBRR register value to generate baud rate
 * ROLE: MASTER or SLAVE symbolic constant
 * RETURN: 0 on success and 1 on "port" failure
 */
int USART_synch_init(uint8_t port, volatile uint16_t ubrr, uint8_t role)
{
    switch (port)
    {
        case 0:
            if (role) // Master or slave
                DDRB |= (1 << DDB0);
            else
                DDRB &= ~(1 << DDB0);
            UBRR0H = (uint8_t)(ubrr >> 8);
            UBRR0L = (uint8_t)ubrr;
            UCSR0B = (1 << TXEN) | (1 << RXEN);
            UCSR0C = (1 << UCSZ0) | (1 << UCSZ1) | (1 << UPM1) | (1 << UMSEL0);
            return 0;
        case 1:
            if (role) // Master or slave
                DDRD |= (1 << DDD4);
            else
                DDRD &= ~(1 << DDD4);
            UBRR1H = (uint8_t)(ubrr >> 8);
            UBRR1L = (uint8_t)ubrr;
            UCSR1B = (1 << TXEN) | (1 << RXEN);
            UCSR1C = (1 << UCSZ0) | (1 << UCSZ1) | (1 << UPM1) | (1 << UMSEL0);
            return 0;
        case 2:
            if (role) // Master or slave
                DDRD |= (1 << DDD7);
            else
                DDRD &= ~(1 << DDD7);
            UBRR2H = (uint8_t)(ubrr >> 8);
            UBRR2L = (uint8_t)ubrr;
            UCSR2B = (1 << TXEN) | (1 << RXEN);
            UCSR2C = (1 << UCSZ0) | (1 << UCSZ1) | (1 << UPM1) | (1 << UMSEL0);
            return 0;
        default:
            return 1;
    }
}

/* Send a character (data) on the selected USART port
 * PORT: USART port number
 * DATA: Data byte to be transmitted
 * RETURN: 0 on success and 1 when "port" failure
 */
int USART_putchar(uint8_t port, volatile char data)
{
    switch (port)
    {
        case 0:
            while (!(UCSR0A & (1 << UDRE)))
                ;
            UDR0 = data;
            return 0;
        case 1:
            while (!(UCSR1A & (1 << UDRE)))
                ;
            UDR1 = data;
            return 0;
        case 2:
            while (!(UCSR2A & (1 << UDRE)))
                ;
            UDR2 = data;
            return 0;
        default:
            return 1;
    }
}

/* Send character array "*s" on USART "port"
 * PORT: USART port number
 * STRING: String constant/character array to be transmitted
 * Return: 0 on success and 1 when "port" failure
 */
int USART_putstr(uint8_t port, const char *string)
{
    while (*string)
        if (USART_putchar(port, *string++)) // If error with port, return 1
            return 1;
    return 0;
}

/* Converts int "value" into char array of "arr_size" in indicated "base"
 * and sends info on USART "port"
 * PORT: USART port number
 * VALUE: Integer (16-bit) value to be transmitted
 * ARR_SIZE: Character array size that will contain the string representation of VALUE
 * BASE: The numerical base in which the VALUE will be transmitted
 * RETURN: 0 on success and 1 on "port" failure
 */
int USART_putint(uint8_t port, int16_t value, uint8_t arr_size, uint8_t base)
{
    char str[arr_size];
    itoa(value, str, base);
    if (USART_putstr(port, str))
        return 1;
    return 0;
}

/* Converts long int "value" into char array of "arr_size" and sends info on USART "port"
 * PORT: USART port number
 * VALUE: Integer (32-bit) value to be transmitted
 * ARR_SIZE: Character array size that will contain the string representation of VALUE
 * RETURN: 0 on success and 1 on "port" failure
 */
int USART_putlongint(uint8_t port, int32_t value, uint8_t arr_size)
{
    char str[arr_size];
    sprintf(str, "%ld", value);
    if (USART_putstr(port, str))
        return 1;
    return 0;
}

/* Converts long int "value" into char array of "arr_size" and sends info on USART "port"
 * PORT: USART port number
 * VALUE: floating point double precision value to be transmitted
 * ARR_SIZE: Character array size that will contain the string representation of VALUE
 * WIDTH: Width of the output that will contain the string representation of VALUE
 * PREC: Floating point precision of the output
 * RETURN: 0 on success and 1 on "port" failure
 */
int USART_putdouble(uint8_t port, double value, uint8_t arr_size, uint8_t width, uint8_t prec)
{
    char str[arr_size];
    dtostrf(value, width, prec, str);
    if (USART_putstr(port, str))
        return 1;
    return 0;
}

/* Gets character received by USART
 * PORT: USART port number
 * RETURN: Received data on success and -1 on "port" failure
 */
char USART_getchar(const uint8_t port)
{
    parity_error = 0;
    frame_error = 0;
    switch (port)
    {
        case 0:
            while (!(UCSR0A & (1 << RXC))) // Wait until data received in buffer
                ;
            if (UCSR0A & (1 << UPE)) // Parity error check
            {
                parity_error++;
                UCSR0A &= ~(1 << UPE);
            }
            if (UCSR0A & (1 << FE)) // Frame error check
            {
                frame_error++;
                UCSR0A &= ~(1 << FE);
            }
            return UDR0;
        case 1:
            while (!(UCSR1A & (1 << RXC)))
                ;
            if (UCSR1A & (1 << UPE))
            {
                parity_error++;
                UCSR1A &= ~(1 << UPE);
            }
            if (UCSR1A & (1 << FE))
            {
                frame_error++;
                UCSR1A &= ~(1 << FE);
            }
            return UDR1;
        case 2:
            while (!(UCSR2A & (1 << RXC)))
                ;
            if (UCSR2A & (1 << UPE))
            {
                parity_error++;
                UCSR2A &= ~(1 << UPE);
            }
            if (UCSR2A & (1 << FE))
            {
                frame_error++;
                UCSR2A &= ~(1 << FE);
            }
            return UDR2;
        default:
            return -1;
    }
}
