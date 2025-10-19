/*
 * config.h
 *
 * Created: 19.10.2025 14:17:06
 * Author: Krzysztof Tomicki
 * Description: All important defines to share across files
 */ 

#ifndef CONFIG_H_
#define CONFIG_H_

// Time of one program iteration
#define LOOP_MS 1000UL
#define LOOP_SEC (LOOP_MS / 1000UL)

// Start memory address for EEPROM modules
#define EEPROM_ADDR 0x0000 

// Number of connected open window sensors
#define WINDOW_COUNT 6

#endif /* CONFIG_H_ */