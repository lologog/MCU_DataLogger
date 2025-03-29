/*
 * rtc.c
 *
 * Created: 29.03.2025 23:55:23
 * Author : Krzysztof Tomicki
 * Description: handle RTC module to get time from it in decimal format
 */

#ifndef RTC_H
#define RTC_H

#include <avr/io.h>

uint8_t bcd_to_dec(uint8_t val);
void rtc_get_time(uint8_t* hour, uint8_t* minute, uint8_t* second);

#endif