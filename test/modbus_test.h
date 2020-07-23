//
// Created by Zhukov on 2020/7/23.
//

#ifndef MODBUSMASTER_MODBUS_TEST_H
#define MODBUSMASTER_MODBUS_TEST_H

void test_modbus(void);
void test_command_error(void);
void test_read_length_error(void);
void test_read_rx_length_error(void);
void test_read_out_of_range_error(void);
void test_read_correct(void);
void test_write_single_rx_length_error(void);
void test_write_single_correct(void);
void test_write_multiple_rx_length_error(void);
void test_write_multiple_rx_length2_error(void);
void test_write_multiple_rx_length3_error(void);
void test_write_multiple_rx_length4_error(void);
void test_write_multiple_out_of_range_error(void);
void test_write_multiple_correct(void);

#endif //MODBUSMASTER_MODBUS_TEST_H
