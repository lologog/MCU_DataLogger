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
#include "i2c.h"
#include "rtc.h"

int main(void) {
	UART_init(103); // 9600 baud at 16 MHz
	I2C_init();     // Start I2C

	uint8_t h, m, s;
	char buffer[32];

	while (1) {
        rtc_get_time(&h, &m, &s);
        sprintf(buffer, "Time: %02d:%02d:%02d\r\n", h, m, s);
        UART_send_string(buffer);
        _delay_ms(1000);
	}
}

