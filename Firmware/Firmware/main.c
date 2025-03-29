/*
 * Firmware.c
 *
 * Created: 29.03.2025 14:58:19
 * Author : Krzysztof Tomicki
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= (1 << PIND2);
    while (1) 
    {
		PORTD |= (1 << PIND2);
		_delay_ms(2000);
		PORTD &= ~(1 << PIND2);
		_delay_ms(2000);
    }
}

