/*
 * i2c.h
 *
 * Created: 29.03.2025 18:29:03
 * Author : Krzysztof Tomicki
 * Description: I2C (TWI) communication interface for ATmega328
 */

#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

void I2C_init(void);
void I2C_start(void);
void I2C_stop(void);
void I2C_write(uint8_t data);
uint8_t I2C_read_ack(void);
uint8_t I2C_read_nack(void);

#endif