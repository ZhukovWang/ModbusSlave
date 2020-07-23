//
// Created by Zhukov on 2020/7/23.
//
#include <stdint.h>
#include "frame_test.h"
#include "../src/config.h"
#include "../src/frame.h"
#include "unity.h"
#include "../src/register.h"

void test_frame(void)
{
    RUN_TEST(test_ascii_frame);
    RUN_TEST(test_rtu_frame);
}

void test_ascii_frame(void)
{
    slave_mode = ASCII_MODE;
    uint8_t rx_data[15] = {0x3A, 0x30, 0x31, 0x30, 0x33, 0x30, 0x30,
                           0x31, 0x30, 0x30, 0x30, 0x30, 0x32, 0x45, 0x41};

    registers.u16[0x10] = 0x55AA;
    registers.u16[0x11] = 0x1122;

    uint8_t result_data[255];
    uint16_t result_length = 0;

    uint8_t res = frame_entry(&rx_data[0], 15, &result_data[0], &result_length);

    TEST_ASSERT_EQUAL_INT16(1, res);
    TEST_ASSERT_EQUAL_INT16(17, result_length);
    TEST_ASSERT_EQUAL_INT8(0x3A, result_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x30, result_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x31, result_data[2]);
    TEST_ASSERT_EQUAL_INT8(0x30, result_data[3]);
    TEST_ASSERT_EQUAL_INT8(0x33, result_data[4]);
    TEST_ASSERT_EQUAL_INT8(0x30, result_data[5]);
    TEST_ASSERT_EQUAL_INT8(0x34, result_data[6]);
    TEST_ASSERT_EQUAL_INT8(0x35, result_data[7]);
    TEST_ASSERT_EQUAL_INT8(0x35, result_data[8]);
    TEST_ASSERT_EQUAL_INT8(0x41, result_data[9]);
    TEST_ASSERT_EQUAL_INT8(0x41, result_data[10]);
    TEST_ASSERT_EQUAL_INT8(0x31, result_data[11]);
    TEST_ASSERT_EQUAL_INT8(0x31, result_data[12]);
    TEST_ASSERT_EQUAL_INT8(0x32, result_data[13]);
    TEST_ASSERT_EQUAL_INT8(0x32, result_data[14]);
    TEST_ASSERT_EQUAL_INT8(0x43, result_data[15]);
    TEST_ASSERT_EQUAL_INT8(0x36, result_data[16]);

    registers.u16[0x10] = 0x0;
    registers.u16[0x11] = 0x0;
}

void test_rtu_frame(void)
{
    slave_mode = RTU_MODE;
    uint8_t rx_data[13] = {0x01, 0x10, 0x00, 0x30, 0x00, 0x02, 0x04,
                           0x55, 0xAA, 0x11, 0x22, 0x4D, 0x1E};

    uint8_t result_data[255];
    uint16_t result_length = 0;

    uint8_t res = frame_entry(&rx_data[0], 13, &result_data[0], &result_length);

    TEST_ASSERT_EQUAL_INT16(1, res);
    TEST_ASSERT_EQUAL_INT16(8, result_length);
    TEST_ASSERT_EQUAL_INT8(0x01, result_data[0]);
    TEST_ASSERT_EQUAL_INT8(0x10, result_data[1]);
    TEST_ASSERT_EQUAL_INT8(0x00, result_data[2]);
    TEST_ASSERT_EQUAL_INT8(0x30, result_data[3]);
    TEST_ASSERT_EQUAL_INT8(0x00, result_data[4]);
    TEST_ASSERT_EQUAL_INT8(0x02, result_data[5]);
    TEST_ASSERT_EQUAL_INT8(0x41, result_data[6]);
    TEST_ASSERT_EQUAL_INT8(0xC7, result_data[7]);

    TEST_ASSERT_EQUAL_INT16(0x55AA, registers.u16[0x30]);
    TEST_ASSERT_EQUAL_INT16(0x1122, registers.u16[0x31]);
}
