//
// Created by Zhukov on 2020/7/23.
//
#include <stdint.h>

#include "frame_conversion.h"

void ascii_frame_to_standard_modbus(uint8_t* rx, uint16_t length, uint8_t* result, uint16_t* result_length)
{
    *result_length = 0;
    for (uint16_t i = 1; i < length; ++i)
    {
        result[*result_length] = (char_to_number(rx[i]) << 4) | char_to_number(rx[i + 1]);
        i++;
        (*result_length)++;
    }
}

void standard_modbus_to_ascii_frame(uint8_t* rx, uint16_t length, uint8_t* result, uint16_t* result_length)
{
    result[*result_length] = 0x3A;
    *result_length = 1;
    for (uint16_t i = 0; i < length; ++i)
    {
        result[*result_length] = number_to_char(rx[i] >> 4);
        (*result_length)++;
        result[*result_length] = number_to_char(rx[i] & 0x0F);
        (*result_length)++;
    }
}

uint8_t char_to_number(const uint8_t ch)
{
    uint8_t value = 0;
    if(ch >= 0x30 && ch <=0x39)
    {
        value = ch - 0x30;
    }
    else if(ch >= 0x41 && ch <= 0x46)
    {
        value = ch - 0x37;
    }
    else if(ch >= 0x61 && ch <= 0x66)
    {
        value = ch - 0x57;
    }
    return value;
}

uint8_t number_to_char(const uint8_t ch)
{
    uint8_t value = 0;

    if(ch <= 9)
    {
        value = ch + 0x30;
    }
    else if(ch >=10 && ch <=15)
    {
        // 大写字母
        value = ch + 0x37;
    }
    return value;
}
