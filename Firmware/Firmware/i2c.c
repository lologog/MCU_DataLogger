/*
 * i2c.c
 *
 * Created: 29.03.2025 18:55:17
 * Author : Krzysztof Tomicki
 * Description: I2C (TWI) low-level implementation for ATmega328
 */

#include "i2c.h"

// start I2C communication - it is necessary to use this function before using I2C
void I2C_init(void) {
    TWSR = 0x00;         // Prescaler = 1
    TWBR = 0x48;         // Bit rate = 100kHz for F_CPU = 16MHz
    TWCR = (1 << TWEN);  // Enable I2C
}

// new I2C transmission
void I2C_start(void) {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // sets TWSTA (I2C start), TWEN (I2C enable) and TWINT (I2C interrupt flag - in TWCR it means allowing for new I2C operation)
    while (!(TWCR & (1 << TWINT))); // wait till end of start which is represented by TWINT = 0
}

// end of transmission
void I2C_stop(void) {
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT); //similar to start but with stop bit instead of start bit
}

// send data (addresses, registers, values)
void I2C_write(uint8_t data) {
    TWDR = data; // I2C data register
    TWCR = (1 << TWEN) | (1 << TWINT); // start sending
    while (!(TWCR & (1 << TWINT))); //wait for the end of sending
}

// informs the target of the message to keep sending - use this when you want to read more than one byte
uint8_t I2C_read_ack(void) {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // TWEA = acknowledge
    while (!(TWCR & (1 << TWINT))); //wait for the end of sending
    return TWDR; // returns read byte 
}

// end of sending - use this when you collected all necessary data
uint8_t I2C_read_nack(void) {
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT))); //wait for the end of sending
    return TWDR;
}