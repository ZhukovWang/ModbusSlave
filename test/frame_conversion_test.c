//
// Created by Zhukov on 2020/7/23.
//

#include "frame_conversion_test.h"

#include <stdint.h>

#include "../src/frame_conversion.h"
#include "unity.h"

void test_conversion(void)
{
    RUN_TEST(test_ascii_frame_to_standard_modbus);
    RUN_TEST(test_standard_modbus_to_ascii_frame);
}

void test_ascii_frame_to_standard_modbus(void)
{
    uint8_t rx_data[13] = {0x3A, 0x30, 0x31, 0x30, 0x33, 0x30, 0x30,
                          0x31, 0x30, 0x30, 0x30, 0x31, 0x30 };

    uint8_t result_data[255];
    uint16_t result_length = 0;

    ascii_frame_to_standard_modbus(&rx_data[0], 13, &result_data[0], &result_length);

    TEST_ASSERT_EQUAL_INT16(6, result_length);
    TEST_ASSERT_EQUAL_INT8(0x01, result_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x03, result_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x00, result_data[2]);
    TEST_ASSERT_EQUAL_INT8(0x10, result_data[3]);
    TEST_ASSERT_EQUAL_INT8(0x00, result_data[4]);
    TEST_ASSERT_EQUAL_INT8(0x10, result_data[5]);
}

void test_standard_modbus_to_ascii_frame(void)
{
    uint8_t rx_data[6] = {0x01, 0x03, 0xAB, 0x10, 0x00, 0x11};

    uint8_t result_data[255];
    uint16_t result_length = 0;

    standard_modbus_to_ascii_frame(&rx_data[0], 6, &result_data[0], &result_length);

    TEST_ASSERT_EQUAL_INT16(13, result_length);
    TEST_ASSERT_EQUAL_INT8(0x3A, result_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x30, result_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x31, result_data[2]);
    TEST_ASSERT_EQUAL_INT8(0x30, result_data[3]);
    TEST_ASSERT_EQUAL_INT8(0x33, result_data[4]);
    TEST_ASSERT_EQUAL_INT8(0x41, result_data[5]);
    TEST_ASSERT_EQUAL_INT8(0x42, result_data[6]);
    TEST_ASSERT_EQUAL_INT8(0x31, result_data[7]);
    TEST_ASSERT_EQUAL_INT8(0x30, result_data[8]);
    TEST_ASSERT_EQUAL_INT8(0x30, result_data[9]);
    TEST_ASSERT_EQUAL_INT8(0x30, result_data[10]);
    TEST_ASSERT_EQUAL_INT8(0x31, result_data[11]);
    TEST_ASSERT_EQUAL_INT8(0x31, result_data[12]);
}
