//
// Created by Zhukov on 2020/7/23.
//

#ifndef MODBUSMASTER_MODBUS_TEST_H
#define MODBUSMASTER_MODBUS_TEST_H

void test_modbus(void);
void test_command_error(void);
void test_read_registers_length_error(void);
void test_read_registers_rx_length_error(void);
void test_read_registers_out_of_range_error(void);
void test_read_registers_correct(void);
void test_write_single_register_rx_length_error(void);
void test_write_single_register_correct(void);
void test_write_multiple_registers_rx_length_error(void);
void test_write_multiple_registers_rx_length2_error(void);
void test_write_multiple_registers_rx_length3_error(void);
void test_write_multiple_registers_rx_length4_error(void);
void test_write_multiple_registers_out_of_range_error(void);
void test_write_multiple_registers_correct(void);
void test_read_coils_rx_length_error(void);
void test_read_coils_length_error(void);
void test_read_coils_out_of_range_error(void);
void test_read_coils_correct(void);
void test_write_single_coil_rx_length_error(void);
void test_write_single_coil_correct(void);

#endif //MODBUSMASTER_MODBUS_TEST_H
