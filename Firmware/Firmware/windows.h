/*
 * windows.h
 *
 * Created: 19.10.2025 14:15:00
 * Author: Krzysztof Tomicki
 * Description: Logic of windows open checking detection
 */ 


#ifndef WINDOWS_H_
#define WINDOWS_H_

#include <avr/io.h>
#include "config.h"

// Data stored about each window
typedef struct
{
	uint32_t opens;
	uint32_t open_secs;
	uint32_t start_time;
	uint8_t state;
} window_data_t;

extern window_data_t windows[WINDOW_COUNT];

void init_windows(void);
void update_windows(uint32_t now);
void print_windows(void);
void windows_reset_data(uint32_t now);

#endif /* WINDOWS_H_ */