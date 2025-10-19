/*
 * eeprom.c
 *
 * Created: 19.10.2025 14:34:07
 * Author: Krzysztof Tomicki
 * Description: Manage data stored in EEPROM
 */ 

#include <string.h>
#include <avr/eeprom.h>

#include "eeprom.h"
#include "config.h"
#include "windows.h"

// Load windows info from EEPROM
void eep_load(void)
{
	eeprom_read_block((void*)windows, (const void*)EEPROM_ADDR, sizeof(windows));
}

// Save windows info to EEPROM
void eep_save(void)
{
	eeprom_update_block((const void*)windows, (void*)EEPROM_ADDR, sizeof(windows));
}

// Check if the EEPROM memory isn't uninitialized
void check_eep_load_data(void)
{
	for (uint8_t i = 0; i < WINDOW_COUNT; i++)
	{
		if (windows[i].opens == 0xFFFFFFFFUL || windows[i].open_secs == 0xFFFFFFFFUL || windows[i].start_time == 0xFFFFFFFFUL || windows[i].state == 0xFF)
		{
			memset(&windows[i], 0, sizeof(window_data_t));
		}
	}
}