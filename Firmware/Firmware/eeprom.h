/*
 * eeprom.h
 *
 * Created: 29.03.2025 21:48:03
 * Author : Krzysztof Tomicki
 * Description: library to work with 24LC1025 EEPROM
 */

#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>

typedef struct {
	uint16_t sensor_value;
	uint8_t status_flag;
} LogEntry;

void eeprom_log_entry(uint16_t value, uint8_t status);
void eeprom_write_bytes(uint32_t addr, uint8_t* data, uint8_t len);
void eeprom_reset_pointer(void);
uint32_t eeprom_get_pointer(void);

#endif