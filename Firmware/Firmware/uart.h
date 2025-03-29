/*
 * uart.h
 *
 * Created: 29.03.2025 15:37:28
 * Author : Krzysztof Tomicki
 * Description: Declarations for UART communication functions for ATmega328.
 */

#ifndef UART_H
#define UART_H

#include <avr/io.h>

void UART_init(uint16_t ubrr);
void UART_send_byte(uint8_t data);
void UART_send_string(const char* str);
char UART_receive_byte(void);

#endif