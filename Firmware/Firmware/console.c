/*
 * console.c
 *
 * Created: 19.10.2025 14:03:07
 * Author: Krzysztof Tomicki
 * Description: Communication with PC terminal via UART
 */ 

#include <stdio.h>

#include "console.h"
#include "config.h"
#include "rtc.h"
#include "windows.h"
#include "uart.h"

extern uint32_t boot_unix;

// Check if there is any data waiting to receive
uint8_t uart_rx_available(void)
{
	return (UCSR0A & (1 << RXC0));
}

// Read one byte from receive buffer
uint8_t uart_rx_getchar(void)
{
	return UDR0;
}

// Print project info after app start
void print_banner(void)
{
	UART_send_string("\r\n=== WindowMonitor v1.0 ===\r\n");
	UART_send_string("UART: 9600 8N1\r\n");
	UART_send_string("Commands: 1=print, 2=reset, 3=uptime\r\n");
	UART_send_string("> ");
}

// Communication logic between PC and the device
void uart_console(uint32_t now)
{
	if (uart_rx_available())
	{
		char cmd = (char)uart_rx_getchar();
		
		if (cmd == '1')
		{
			print_windows();
			UART_send_string("> ");
		}
		else if (cmd == '2')
		{
			windows_reset_data(now);
			UART_send_string("OK: reset all windows\r\n");
			UART_send_string("> ");
		}
		else if (cmd == '3')
		{
			uint32_t time = rtc_get_unix();
			uint32_t dt = (time >= boot_unix) ? (time - boot_unix) : 0;

			char buf[32];
			uint32_t hh = dt / 3600;
			uint32_t mm = (dt % 3600) / 60;
			uint32_t ss = dt % 60;
			sprintf(buf, "Uptime: %02lu:%02lu:%02lu\r\n",
			(unsigned long)hh, (unsigned long)mm, (unsigned long)ss);

			UART_send_string(buf);
			UART_send_string("> ");
		}
		else
		{
			UART_send_string("Commands: 1=print, 2=reset, 3=uptime\r\n");
			UART_send_string("> ");
		}
	}
}