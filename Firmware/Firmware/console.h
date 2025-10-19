/*
 * console.h
 *
 * Created: 19.10.2025 14:04:00
 * Author: Krzysztof Tomicki
 * Description: Communication with PC terminal via UART
 */ 


#ifndef CONSOLE_H_
#define CONSOLE_H_

uint8_t uart_rx_available(void);
uint8_t uart_rx_getchar(void);
void print_banner(void);
void uart_console(uint32_t now);



#endif /* CONSOLE_H_ */