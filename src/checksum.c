//
// Created by Zhukov on 2020/7/23.
//

#include <stdint.h>

#include "checksum.h"

uint8_t checksum_lrc(uint8_t* data, uint16_t length)
{
    uint8_t lrc_result = 0;

    for (uint16_t i = 0; i < length; ++i)
    {
        lrc_result = (lrc_result + data[i]) & 0xFF;
    }

    lrc_result = (((lrc_result ^ 0xFF) + 1) & 0xFF);

    return lrc_result;
}

uint16_t checksum_crc(uint8_t* data, uint16_t length)
{
    uint16_t crc_result = 0xFFFF;
    for (uint16_t i = 0; i < length; ++i)
    {
        crc_result ^= data[i];
        for (uint16_t j = 0; j < 8; ++j)
        {
            if ((crc_result & 0x01) != 0)
            {
                crc_result = (uint16_t) ((crc_result >> 1) ^ 0xa001);
            }
            else
            {
                crc_result = (uint16_t) (crc_result >> 1);
            }
        }
    }

    uint16_t crc_result_temp = crc_result >> 8;
    crc_result = (uint16_t)((crc_result << 8) | crc_result_temp);
    return crc_result;
}