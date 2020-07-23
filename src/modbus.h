//
// Created by Zhukov on 2020/7/23.
//

#ifndef MODBUSMASTER_MODBUS_H
#define MODBUSMASTER_MODBUS_H

int8_t modbus_entry(uint8_t* rx, uint16_t rx_length, uint8_t* tx, uint16_t* tx_length);
int8_t command_error(uint8_t *rx, uint16_t rx_length, uint8_t *tx, uint16_t *tx_length);
int8_t command_read_registers(uint8_t *rx, uint16_t rx_length, uint8_t *tx, uint16_t *tx_length);
int8_t command_write_single_registers(uint8_t *rx, uint16_t rx_length, uint8_t *tx, uint16_t *tx_length);
int8_t command_write_multiple_registers(uint8_t *rx, uint16_t rx_length, uint8_t *tx, uint16_t *tx_length);

#endif //MODBUSMASTER_MODBUS_H
