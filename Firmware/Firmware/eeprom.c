/*
 * eeprom_logger.c
 *
 * Created: 29.03.2025 23:08:01
 * Author : Krzysztof Tomicki
 * Description: library to work with 24LC1025 EEPROM
 */

#include "eeprom.h"
#include "i2c.h"
#include <util/delay.h>

// EEPROM base addresses depends on A0 - A2 connection on the chip
#define EEPROM1_ADDR_BASE 0xA0
#define EEPROM2_ADDR_BASE 0xA2

// Global logical address
static uint32_t eeprom_log_addr = 0;

// returns address of the EEPROM chip in I2C bus
uint8_t get_eeprom_device_addr(uint32_t addr) {
    if (addr < 65536) {
        return EEPROM1_ADDR_BASE;              // Chip 1, bank 0
    } else if (addr < 131072) {
        return EEPROM1_ADDR_BASE | 0x02;       // Chip 1, bank 1
    } else if (addr < 196608) {
        return EEPROM2_ADDR_BASE;              // Chip 2, bank 0
    } else {
        return EEPROM2_ADDR_BASE | 0x02;       // Chip 2, bank 1
    }
}

// function to send data
void eeprom_write_bytes(uint32_t addr, uint8_t* data, uint8_t len) {
    uint8_t dev_addr = get_eeprom_device_addr(addr);
    uint16_t mem_addr = addr % 65536;

    I2C_start();
    I2C_write(dev_addr); //communicate with correct memory chip
    I2C_write((mem_addr >> 8) & 0xFF); // first half of the address where data should be stored
    I2C_write(mem_addr & 0xFF); // second half of the address

	// send actual data
    for (uint8_t i = 0; i < len; i++) {
        I2C_write(data[i]);
    }

    I2C_stop();
    _delay_ms(5);
}

// use this function to save data automatically
void eeprom_log_entry(uint16_t value, uint8_t status) {
    LogEntry entry;
    entry.sensor_value = value;
    entry.status_flag = status;

    eeprom_write_bytes(eeprom_log_addr, (uint8_t*)&entry, sizeof(entry));
    eeprom_log_addr += sizeof(entry);
}

// sets log address pointer to the start position
void eeprom_reset_pointer(void) {
    eeprom_log_addr = 0;
}

// return address of the pointer
uint32_t eeprom_get_pointer(void) {
    return eeprom_log_addr;
}  
