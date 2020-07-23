//
// Created by Zhukov on 2020/7/23.
//

#ifndef MODBUSMASTER_FRAME_CONVERSION_H
#define MODBUSMASTER_FRAME_CONVERSION_H

uint8_t char_to_number(const uint8_t ch);
uint8_t number_to_char(const uint8_t ch);
void ascii_frame_to_standard_modbus(uint8_t* rx, uint16_t length, uint8_t* result, uint16_t* result_length);
void standard_modbus_to_ascii_frame(uint8_t* rx, uint16_t length, uint8_t* result, uint16_t* result_length);

#endif //MODBUSMASTER_FRAME_CONVERSION_H
