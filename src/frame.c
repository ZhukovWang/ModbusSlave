//
// Created by Zhukov on 2020/7/23.
//
#include <stdint.h>

#include "frame.h"
#include "config.h"
#include "checksum.h"
#include "modbus.h"
#include "frame_conversion.h"

int8_t frame_entry(uint8_t* rx_data, uint16_t rx_length, uint8_t* tx_data, uint16_t* tx_length)
{
    if (slave_mode == RTU_MODE)
    {
        uint16_t checksum = checksum_crc(rx_data, rx_length - 2);

        if (checksum == ((rx_data[rx_length - 2] << 8) | rx_data[rx_length - 1]))
        {
            uint8_t res = modbus_entry(rx_data, rx_length - 2, tx_data, tx_length);

            if (res != 0)
            {
                uint16_t tx_checksum = checksum_crc(tx_data, *tx_length);
                tx_data[*tx_length] = tx_checksum >> 8;
                (*tx_length)++;
                tx_data[*tx_length] = tx_checksum & 0x00FF;
                (*tx_length)++;
                return res;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            tx_data[0] = slave_id;
            tx_data[1] = rx_data[1] | (1 << 7);
            tx_data[2] = 0x07;
            *tx_length = 3;
            return 1;
        }
    }
    else if (slave_mode == ASCII_MODE)
    {
        uint8_t conversion_result_data[rx_length];
        uint16_t conversion_result_length = 0;
        ascii_frame_to_standard_modbus(rx_data, rx_length, &conversion_result_data[0], &conversion_result_length);

        uint8_t checksum = checksum_lrc(&conversion_result_data[0], conversion_result_length - 1);

        if (checksum == conversion_result_data[conversion_result_length - 1])
        {
            uint8_t conversion_result_data2[255];
            uint16_t conversion_result_length2 = 0;

            uint8_t res = modbus_entry(&conversion_result_data[0], conversion_result_length - 1, &conversion_result_data2[0], &conversion_result_length2);

            if (res != 0)
            {
                uint8_t tx_checksum = checksum_lrc(&conversion_result_data2[0], conversion_result_length2);

                conversion_result_data2[conversion_result_length2] = tx_checksum;
                conversion_result_length2++;

                standard_modbus_to_ascii_frame(&conversion_result_data2[0], conversion_result_length2, tx_data, tx_length);
                return res;
            }
            else
            {
                return  0;
            }
        }
        else
        {
            tx_data[0] = slave_id;
            tx_data[1] = rx_data[1] | (1 << 7);
            tx_data[2] = 0x07;
            *tx_length = 3;
            return 1;

        }
    }
}