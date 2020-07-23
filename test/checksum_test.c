//
// Created by Zhukov on 2020/7/23.
//
#include <stdint.h>

#include "checksum_test.h"
#include "../src/checksum.h"
#include "unity.h"

void test_checksum(void)
{
    RUN_TEST(test_checksum_lrc);
    RUN_TEST(test_checksum_crc);
}

void test_checksum_lrc(void)
{
    uint8_t data[6] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02};
    uint8_t lrc_result = checksum_lrc(&data[0], 6);

    TEST_ASSERT_EQUAL_INT8(0xFA, lrc_result);
}

void test_checksum_crc(void)
{
    uint8_t data[6] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02};
    uint16_t crc_result = checksum_crc(&data[0], 6);

    TEST_ASSERT_EQUAL_INT16(0xC40B, crc_result);
}