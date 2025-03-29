/*
 * Firmware.c
 *
 * Created: 29.03.2025 14:58:19
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

int main(void) {
    UART_init(103);         // 9600 baud at 16 MHz
    I2C_init();             // init I2C
    eeprom_reset_pointer(); // start from EEPROM address 0

    // configure D2–D7 (PD2–PD7) as INPUT
    DDRD &= ~(0b11111100);  // clear bits 2–7 (input mode)

    uint8_t h, m, s;
    uint8_t last_logged_second = 255;
    char buffer[64];

    while (1) {
        rtc_get_time(&h, &m, &s);

        // display time every second
        sprintf(buffer, "Time: %02d:%02d:%02d\r\n", h, m, s);
        UART_send_string(buffer);

		// log every 10 seconds
		if ((s % 10 == 0) && (s != last_logged_second)) {
			last_logged_second = s;

			uint8_t pin_state = PIND & 0b11111100;  // read D2–D7 (PD2–PD7)
			eeprom_log_entry(pin_state, s);         // save pin state + seconds

			// print via UART message to show which pins are high and low
			uint8_t d2 = (pin_state >> 2) & 0x01;
			uint8_t d3 = (pin_state >> 3) & 0x01;
			uint8_t d4 = (pin_state >> 4) & 0x01;
			uint8_t d5 = (pin_state >> 5) & 0x01;
			uint8_t d6 = (pin_state >> 6) & 0x01;
			uint8_t d7 = (pin_state >> 7) & 0x01;

			sprintf(buffer,
			"Logged pins: D2=%d D3=%d D4=%d D5=%d D6=%d D7=%d (status %02d)\r\n",
			d2, d3, d4, d5, d6, d7, s);
	
			UART_send_string(buffer);
		}
        _delay_ms(200);
    }
}
