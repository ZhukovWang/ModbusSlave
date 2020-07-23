//
// Created by Zhukov on 2020/7/23.
//

#include "all_test.h"

#include "unity.h"
#include "checksum_test.h"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

int test_all(void)
{
    UNITY_BEGIN();
    checksum_test();
    return UNITY_END();
}

void checksum_test(void)
{
    RUN_TEST(test_checksum_lrc);
    RUN_TEST(test_checksum_crc);
}