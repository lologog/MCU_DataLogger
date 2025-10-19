/*
 * Firmware.c
 *
 * Created: 19.10.2025 14:58:19
 * Author : Krzysztof Tomicki
 * Description: Main file
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/eeprom.h>

#include "uart.h"
#include "i2c.h"
#include "rtc.h"
#include "console.h"
#include "windows.h"
#include "config.h"
#include "eeprom.h"

const uint8_t window_pins[WINDOW_COUNT] =
{
	PD2, PD3, PD4, PD5, PD6, PD7
};

window_data_t windows[WINDOW_COUNT];
uint32_t boot_unix = 0;

int main(void) 
{
	UART_init(103); //9600 baud at 16 MHz
	I2C_init();
	init_windows();
	print_banner();
	
	boot_unix = rtc_get_unix();
	
	while (1)
	{
		uint32_t now = rtc_get_unix();
		
		update_windows(now);
		uart_console(now);
	
		_delay_ms(LOOP_MS);
	}
}
