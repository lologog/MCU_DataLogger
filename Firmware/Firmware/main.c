/*
 * Firmware.c
 *
 * Created: 29.03.2025 14:58:19
 * Author : Krzysztof Tomicki
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void) {
	UART_init(103); // 9600 baud at 16MHz

	while (1) {
		UART_send_string("Hello from ATmega328!\r\n");
		_delay_ms(1000);
	}
}

