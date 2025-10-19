/*
 * windows.c
 *
 * Created: 19.10.2025 14:14:28
 * Author: Krzysztof Tomicki
 * Description: Logic of windows open checking detection
 */ 

#include "windows.h"
#include "config.h"
#include "stdio.h"
#include "rtc.h"
#include "eeprom.h"
#include "uart.h"

extern uint32_t boot_unix;
extern const uint8_t window_pins[WINDOW_COUNT];

// Set windows info after start
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
	
	eep_load();
	check_eep_load_data();
}

// Windows data update logic
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
			eep_save();
		}
		
		// Count time when the window is opened
		if (windows[i].state == 1 && windows[i].start_time > 0)
		{
			windows[i].open_secs += LOOP_SEC;
		}
	}
}

// Print windows data via UART to PC
void print_windows(void)
{
	UART_send_string("\r\n-----------------------------\r\n");
	
	char buffer[64];

	for (uint8_t i = 0; i < WINDOW_COUNT; i++)
	{
		sprintf(buffer, "Window %d: %s | Opens: %lu | OpenSecs: %lu\r\n", i + 1, windows[i].state ? "OPEN " : "CLOSED", windows[i].opens, windows[i].open_secs);
		UART_send_string(buffer);
	}

	UART_send_string("-----------------------------\r\n");
}

// Reset current data after reset frame
void windows_reset_data(uint32_t now)
{
	for (uint8_t i = 0; i < WINDOW_COUNT; i++)
	{
		windows[i].opens = 0;
		windows[i].open_secs = 0;
		uint8_t hw = !(PIND & (1 << window_pins[i]));
		windows[i].state = hw;
		windows[i].start_time = hw ? now : 0;
	}
	
	boot_unix = now;
	eep_save();
}