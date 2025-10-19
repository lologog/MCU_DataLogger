/*
 * Firmware.c
 *
 * Created: 19.10.2025 14:58:19
 * Author : Krzysztof Tomicki
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"
#include "i2c.h"
#include "rtc.h"
#include "eeprom.h"

#define WINDOW_COUNT 6

const uint8_t window_pins[WINDOW_COUNT] = 
{
	PD2, PD3, PD4, PD5, PD6, PD7
};

typedef struct  
{
	uint32_t opens;
	uint32_t open_secs;
	uint32_t start_time;
	uint8_t state;
} window_data_t;

window_data_t windows[WINDOW_COUNT];

void init_windows(void)
{
	for (uint8_t i = 0; i < WINDOW_COUNT; i++)
	{
		DDRD &= ~(1 << window_pins[i]);
		PORTD |= (1 << window_pins[i]);

		windows[i].opens = 0;
		windows[i].open_secs = 0;
		windows[i].start_time = 0;
		windows[i].state = 0;
	}
}

void update_windows(uint32_t now)
{
	// Send current windows state
	for (uint8_t i = 0; i < WINDOW_COUNT; i++)
	{
		uint8_t state = !(PIND & (1 << window_pins[i])); // 0 = CLOSED, 1 = OPEN
				
		// Detect change
		if (state != windows[i].state)
		{
			if (state == 1)
			{
				// Window is opened
				windows[i].opens++;
				windows[i].start_time = now;
			}
			else
			{
				// Window is closed
				if (windows[i].start_time > 0)
				{
					windows[i].start_time = 0;
				}
			}
					
			windows[i].state = state;
		}
				
		// Count time when the window is opened
		if (windows[i].state == 1 && windows[i].start_time > 0)
		{
			windows[i].open_secs++;
		}
	}
}

void print_windows(void)
{
	char buffer[64];

	for (uint8_t i = 0; i < WINDOW_COUNT; i++)
	{
		sprintf(buffer, "Window %d: %s | Opens: %lu | OpenSecs: %lu\r\n", i + 1, windows[i].state ? "OPEN " : "CLOSED", windows[i].opens, windows[i].open_secs);
		UART_send_string(buffer);
	}

	UART_send_string("-----------------------------\r\n");
}

int main(void) 
{
	UART_init(103); //9600 baud at 16 MHz
	I2C_init();
	init_windows();
	
	uint8_t h, m, s;
	char buffer[64];
	
	while (1)
	{
		// Get time from RTC module
		rtc_get_time(&h, &m, &s);
		uint32_t now = rtc_get_unix();
		
		sprintf(buffer, "Time since start: %02d:%02d:%02d\r\n", h, m, s);
		UART_send_string(buffer);
		
		update_windows(now);
		print_windows();
	
		_delay_ms(1000);
	}
}
