/*
 * Date: 16/11/2021
 * Author: Abdelrahman Gohar
 * Target µC: ATmega324PB
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/iom324pb.h>

/**********************************
 *  Write byte to EEPROM
 * address: Address to the location in EEPROM
 * data: Data to be written in EEPROM
 * Return: void
 **********************************/
void eeprom_write(uint8_t data, uint16_t address)
{
    while (EECR & (1 << EEPE)) // Wait until write operation is done
        ;
    while (SPMCSR & (1 << SPMEN))
        ;
    EEAR = address;      // Address in EEPROM
    EEDR = data;         // Data to write to EEPROM
    EECR = (1 << EEMPE); // Enable master write bit
    EECR |= (1 << EEPE); // Start write operation
}

/**********************************
 * Read byte from EEPROM
 * address: Address to the location in EEPROM
 * Return: Value read from specified location in EEPROM
 **********************************/
uint8_t eeprom_read(uint16_t address)
{
    while (EECR & (1 << EEPE)) // Wait until write operation is done
        ;
    EEAR = address;      // Address in EEPROM
    EECR |= (1 << EERE); // Start reading operation
    return EEDR;         // Return read value from EEPROM
}