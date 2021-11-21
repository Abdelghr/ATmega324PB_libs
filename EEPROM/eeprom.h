/*
 * Date: 16/11/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

#ifndef F_CPU
#define F_CPU
#endif

#include <stdint.h>

void eeprom_write(uint8_t data, uint16_t address);
uint8_t eeprom_read(uint16_t address);