//
// Created by Zhukov on 2020/7/23.
//
#include <stdint.h>

#include "modbus_test.h"
#include "../src/modbus.h"
#include "unity.h"
#include "../src/register.h"

void test_modbus(void)
{
    RUN_TEST(test_command_error);
    RUN_TEST(test_read_rx_length_error);
    RUN_TEST(test_read_length_error);
    RUN_TEST(test_read_out_of_range_error);
    RUN_TEST(test_read_correct);
    RUN_TEST(test_write_single_rx_length_error);
    RUN_TEST(test_write_single_correct);
}

void test_command_error(void)
{
    uint8_t rx_data[6] = {0x01, 0x0C, 0x00, 0x00, 0x00, 0x02};
    uint8_t tx_data[255];
    uint16_t tx_length = 0;
    uint8_t result = modbus_entry(&rx_data[0], 6, &tx_data[0], &tx_length);

    TEST_ASSERT_EQUAL_INT8(0x01, result);
    TEST_ASSERT_EQUAL_INT16(3, tx_length);
    TEST_ASSERT_EQUAL_INT8(0x01, tx_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x8C, tx_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x01, tx_data[2]);
}

void test_read_rx_length_error(void)
{
    uint8_t rx_data[7] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0x01};
    uint8_t tx_data[255];
    uint16_t tx_length = 0;
    uint8_t result = modbus_entry(&rx_data[0], 7, &tx_data[0], &tx_length);

    TEST_ASSERT_EQUAL_INT8(0x01, result);
    TEST_ASSERT_EQUAL_INT16(3, tx_length);
    TEST_ASSERT_EQUAL_INT8(0x01, tx_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x83, tx_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x07, tx_data[2]);
}

void test_read_length_error(void)
{
    uint8_t rx_data[6] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x21};
    uint8_t tx_data[255];
    uint16_t tx_length = 0;
    uint8_t result = modbus_entry(&rx_data[0], 6, &tx_data[0], &tx_length);

    TEST_ASSERT_EQUAL_INT8(0x01, result);
    TEST_ASSERT_EQUAL_INT16(3, tx_length);
    TEST_ASSERT_EQUAL_INT8(0x01, tx_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x83, tx_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x03, tx_data[2]);
}

void test_read_out_of_range_error(void)
{
    uint8_t rx_data[6] = {0x01, 0x03, 0xFF, 0xF0, 0x00, 0x20};
    uint8_t tx_data[255];
    uint16_t tx_length = 0;
    uint8_t result = modbus_entry(&rx_data[0], 6, &tx_data[0], &tx_length);

    TEST_ASSERT_EQUAL_INT8(0x01, result);
    TEST_ASSERT_EQUAL_INT16(3, tx_length);
    TEST_ASSERT_EQUAL_INT8(0x01, tx_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x83, tx_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x07, tx_data[2]);
}

void test_read_correct(void)
{
    registers.u16[0] = 0x55AA;
    registers.u16[1] = 0xFF00;

    uint8_t rx_data[6] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02};
    uint8_t tx_data[255];
    uint16_t tx_length = 0;
    uint8_t result = modbus_entry(&rx_data[0], 6, &tx_data[0], &tx_length);

    TEST_ASSERT_EQUAL_INT8(0x01, result);
    TEST_ASSERT_EQUAL_INT16(7, tx_length);
    TEST_ASSERT_EQUAL_INT8(0x01, tx_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x03, tx_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x04, tx_data[2]);
    TEST_ASSERT_EQUAL_INT8(0x55, tx_data[3]);
    TEST_ASSERT_EQUAL_INT8(0xAA, tx_data[4]);
    TEST_ASSERT_EQUAL_INT8(0xFF, tx_data[5]);
    TEST_ASSERT_EQUAL_INT8(0x00, tx_data[6]);

    registers.u16[0] = 0x0;
    registers.u16[1] = 0x0;
}

void test_write_single_rx_length_error(void)
{
    uint8_t rx_data[7] = {0x01, 0x06, 0x00, 0x00, 0x00, 0x02, 0x01};
    uint8_t tx_data[255];
    uint16_t tx_length = 0;
    uint8_t result = modbus_entry(&rx_data[0], 7, &tx_data[0], &tx_length);

    TEST_ASSERT_EQUAL_INT8(0x01, result);
    TEST_ASSERT_EQUAL_INT16(3, tx_length);
    TEST_ASSERT_EQUAL_INT8(0x01, tx_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x86, tx_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x07, tx_data[2]);
}

void test_write_single_correct(void)
{
    uint8_t rx_data[6] = {0x01, 0x06, 0x00, 0x10, 0x55, 0xAA};
    uint8_t tx_data[255];
    uint16_t tx_length = 0;
    uint8_t result = modbus_entry(&rx_data[0], 6, &tx_data[0], &tx_length);

    TEST_ASSERT_EQUAL_INT8(0x01, result);
    TEST_ASSERT_EQUAL_INT16(6, tx_length);
    TEST_ASSERT_EQUAL_INT8(0x01, tx_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x06, tx_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x00, tx_data[2]);
    TEST_ASSERT_EQUAL_INT8(0x10, tx_data[3]);
    TEST_ASSERT_EQUAL_INT8(0x55, tx_data[4]);
    TEST_ASSERT_EQUAL_INT8(0xAA, tx_data[5]);
    TEST_ASSERT_EQUAL_INT16(0x55AA, registers.u16[0x10]);
}
