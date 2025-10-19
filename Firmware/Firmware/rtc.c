/*
 * rtc.c
 *
 * Created: 29.03.2025 23:57:43
 * Author : Krzysztof Tomicki
 * Description: low-level handling RTC module to get time from it in decimal format
 */

#include "rtc.h"
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

uint32_t rtc_get_unix(void)
{
	uint8_t h, m, s;
	rtc_get_time(&h, &m, &s);
	
	return h * 3600UL + m * 60UL + s;
}