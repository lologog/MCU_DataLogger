/*
 * uart.c
 *
 * Created: 29.03.2025 15:38:02
 * Author : Krzysztof Tomicki
 * Description: UART communication functions for ATmega328.
 */

#include "uart.h"

// start UART communication - it is necessary to use this function before using UART
void UART_init(uint16_t ubrr) {
    UBRR0H = (ubrr >> 8);							   // UBRR - 16 bit register responsible for UART baud rate
    UBRR0L = ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);              // UCSR0B - Enable receiver and transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);            // UCSR0C - transimssion configuration - 8-bit data, no parity, 1 stop bit
}

void UART_send_byte(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0)));                 // Wait until buffer (UDRE0) is empty (UCSR0A is a status register in UART)
    UDR0 = data;                                      // Send byte (UDR - USART Data register)
}

void UART_send_string(const char* str) {
    while (*str) {
        UART_send_byte(*str++);                       // Send each character
    }
}

char UART_receive_byte(void) {
    while (!(UCSR0A & (1 << RXC0)));                  // Wait for incoming data (RXC - register receive complete)
    return UDR0;                                      // Return received byte
}