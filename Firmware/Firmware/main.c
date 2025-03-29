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
// function to change BCD data format do decinal data format
uint8_t bcd_to_dec(uint8_t val) {
	return (val >> 4) * 10 + (val & 0x0F);
}

// function to communicate with RTC module (DS1337S+) via I2C
void rtc_get_time(uint8_t* hour, uint8_t* minute, uint8_t* second) {
	I2C_start();
	I2C_write(0xD0);      // RTC address (write)
	I2C_write(0x00);      // Start from register 0 (seconds)
	I2C_start();
	I2C_write(0xD1);      // RTC address (read)

	*second = bcd_to_dec(I2C_read_ack());
	*minute = bcd_to_dec(I2C_read_ack());
	*hour   = bcd_to_dec(I2C_read_nack());

	I2C_stop();
}

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

