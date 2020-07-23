//
// Created by Zhukov on 2020/7/23.
//
#include <stdint.h>

#include "modbus.h"
#include "config.h"
#include "register.h"

#define ERROR_CODE_COMMAND_ERROR 0x01
#define ERROR_CODE_ADRRESS_ERROR 0x02
#define ERROR_CODE_DATA_ERROR 0x03
#define ERROR_CODE_OTHER_ERROR 0x07

#define READ_REGISTERS_COMMAND 0x03
#define WRITE_SINGLE_REGISTERS_COMMAND 0x06
#define WRITE_MULTIPLE_REGISTERS_COMMAND 0x10

/*
 * modbus protocol entry
 * return: 0: do nothing 1:need reply
 */
int8_t modbus_entry(uint8_t *rx, uint16_t rx_length, uint8_t *tx, uint16_t *tx_length)
{
    if (rx[0] == slave_id)
    {
        if (rx[1] == READ_REGISTERS_COMMAND)
        {
            command_read_registers(rx, rx_length, tx, tx_length);
        }
        else if (rx[1] == WRITE_SINGLE_REGISTERS_COMMAND)
        {
            command_write_single_registers(rx, rx_length, tx, tx_length);
        }
        else if (rx[1] == WRITE_MULTIPLE_REGISTERS_COMMAND)
        {
            command_write_multiple_registers(rx, rx_length, tx, tx_length);
        }
        else
        {
            command_error(rx, rx_length, tx, tx_length);
        }
    }
    else
    {
        return 0;
    }
}

int8_t command_error(uint8_t *rx, uint16_t rx_length, uint8_t *tx, uint16_t *tx_length)
{
    tx[0] = slave_id;
    tx[1] = rx[1] | (1 << 7);
    tx[2] = ERROR_CODE_COMMAND_ERROR;
    *tx_length = 3;
    return 1;
}

int8_t command_read_registers(uint8_t *rx, uint16_t rx_length, uint8_t *tx, uint16_t *tx_length)
{
    if (rx_length != 6) //rx length is wrong
    {
        tx[0] = slave_id;
        tx[1] = rx[1] | (1 << 7);
        tx[2] = ERROR_CODE_OTHER_ERROR;
        *tx_length = 3;
        return 1;
    }
    else
    {
        uint16_t read_address = (rx[2] << 8) | rx[3];
        uint16_t read_length = (rx[4] << 8) | rx[5];

        if (read_address >= MIN_READ_REGISTER && read_address <= MAX_READ_REGISTER) //read address in the scope
        {
            if (read_length > MAX_READ_LENGTH) //read length in the scope
            {
                tx[0] = slave_id;
                tx[1] = rx[1] | (1 << 7);
                tx[2] = ERROR_CODE_DATA_ERROR;
                *tx_length = 3;
                return 1;
            }
            else
            {
                if ((uint32_t)((uint32_t)read_address + (uint32_t)read_length) >= MAX_READ_REGISTER) //read register in the scope
                {
                    tx[0] = slave_id;
                    tx[1] = rx[1] | (1 << 7);
                    tx[2] = ERROR_CODE_OTHER_ERROR;
                    *tx_length = 3;
                    return 1;
                }
                else
                {
                    // all good
                    tx[0] = slave_id;
                    tx[1] = READ_REGISTERS_COMMAND;
                    tx[2] = read_length * 2;
                    for (uint32_t i = 0; i < read_length; ++i)
                    {
                        tx[2 * i + 3] = registers.u16[read_address + i] >> 8;
                        tx[2 * i + 1 + 3] = registers.u16[read_address + i];
                    }
                    *tx_length = 3 + read_length * 2;
                    return 1;
                }
            }
        }
        else
        {
            tx[0] = slave_id;
            tx[1] = rx[1] | (1 << 7);
            tx[2] = ERROR_CODE_ADRRESS_ERROR;
            *tx_length = 3;
            return 1;
        }
    }
}

int8_t command_write_single_registers(uint8_t *rx, uint16_t rx_length, uint8_t *tx, uint16_t *tx_length)
{
    if (rx_length != 6) //rx length is wrong
    {
        tx[0] = slave_id;
        tx[1] = rx[1] | (1 << 7);
        tx[2] = ERROR_CODE_OTHER_ERROR;
        *tx_length = 3;
        return 1;
    }
    else
    {
        uint16_t write_address = (rx[2] << 8) | rx[3];
        uint16_t write_data = (rx[4] << 8) | rx[5];

        if (write_address >= MIN_WRITE_SINGLE_REGISTER && write_address <= MAX_WRITE_SINGLE_REGISTER) //write address in the scope
        {
            // all good
            registers.u16[write_address] = write_data;

            tx[0] = slave_id;
            tx[1] = WRITE_SINGLE_REGISTERS_COMMAND;
            tx[2] = write_address >> 8;
            tx[3] = write_address & 0x00FF;
            tx[4] = write_data >> 8;
            tx[5] = write_data & 0x00FF;
            *tx_length = 6;
            return 1;
        }
        else
        {
            tx[0] = slave_id;
            tx[1] = rx[1] | (1 << 7);
            tx[2] = ERROR_CODE_ADRRESS_ERROR;
            *tx_length = 3;
            return 1;
        }
    }
}

int8_t command_write_multiple_registers(uint8_t *rx, uint16_t rx_length, uint8_t *tx, uint16_t *tx_length)
{
    if (((rx_length & 1) == 0) || (rx_length < 9)) //rx length is wrong
    {
        tx[0] = slave_id;
        tx[1] = rx[1] | (1 << 7);
        tx[2] = ERROR_CODE_OTHER_ERROR;
        *tx_length = 3;
        return 1;
    }
    else
    {
        uint16_t write_address = (rx[2] << 8) | rx[3];
        uint16_t write_word_length = (rx[4] << 8) | rx[5];
        uint16_t write_byte_length = rx[6];

        if (write_byte_length != write_word_length * 2) //write length is not correct
        {
            tx[0] = slave_id;
            tx[1] = rx[1] | (1 << 7);
            tx[2] = ERROR_CODE_DATA_ERROR;
            *tx_length = 3;
            return 1;
        }

        if (write_word_length * 2 + 7 != rx_length)
        {
            tx[0] = slave_id;
            tx[1] = rx[1] | (1 << 7);
            tx[2] = ERROR_CODE_OTHER_ERROR;
            *tx_length = 3;
            return 1;
        }

        if (write_address >= MIN_WRITE_MULTIPLE_REGISTERS && write_address <= MAX_WRITE_MULTIPLE_REGISTERS) //write address in the scope
        {
            if (write_word_length > MAX_WRITE_MULTIPLE_LENGTH) //write length in the scope
            {
                tx[0] = slave_id;
                tx[1] = rx[1] | (1 << 7);
                tx[2] = ERROR_CODE_DATA_ERROR;
                *tx_length = 3;
                return 1;
            }
            else
            {
                if ((uint32_t)((uint32_t)write_address + (uint32_t)write_word_length) >= MAX_WRITE_MULTIPLE_REGISTERS) //write register in the scope
                {
                    tx[0] = slave_id;
                    tx[1] = rx[1] | (1 << 7);
                    tx[2] = ERROR_CODE_OTHER_ERROR;
                    *tx_length = 3;
                    return 1;
                }
                else
                {
                    // all good
                    for (int16_t i = 0; i < write_word_length; ++i)
                    {
                        registers.u16[write_address + i] = (rx[7 + i * 2] << 8) | (rx[7 + i * 2 + 1]);
                    }

                    tx[0] = slave_id;
                    tx[1] = WRITE_MULTIPLE_REGISTERS_COMMAND;
                    tx[2] = write_address >> 8;
                    tx[3] = write_address & 0x00FF;
                    tx[4] = write_word_length >> 8;
                    tx[5] = write_word_length & 0x00FF;
                    *tx_length = 6;
                    return 1;
                }
            }
        }
        else
        {
            tx[0] = slave_id;
            tx[1] = rx[1] | (1 << 7);
            tx[2] = ERROR_CODE_ADRRESS_ERROR;
            *tx_length = 3;
            return 1;
        }
    }
}