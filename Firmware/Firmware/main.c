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

int main(void) 
{
	UART_init(103); //9600 baud at 16 MHz
	I2C_init();
	
	uint8_t h, m, s;
	char buffer[64];
	
	for (uint8_t i = 0; i < WINDOW_COUNT; i++)
	{
		DDRD &= ~(1 << window_pins[i]); // Set PD2-PD7 pins as inputs
		PORTD |= (1 << window_pins[i]); // Set pull-ups
	}
	
	while (1)
	{
		// Get time from RTC module
		rtc_get_time(&h, &m, &s);
		sprintf(buffer, "Time: %02d:%02d:%02d\r\n", h, m, s);
		UART_send_string(buffer);
		
		// Send current windows state
		for (uint8_t i = 0; i < WINDOW_COUNT; i++)
		{
			uint8_t state = !(PIND & (1 << window_pins[i])); // 0 = CLOSED, 1 = OPEN
			sprintf(buffer, "Window %d: %s\r\n", i + 1, state ? "OPEN" : "CLOSED");
			UART_send_string(buffer);
		}
		
		_delay_ms(1000);
	}
}
