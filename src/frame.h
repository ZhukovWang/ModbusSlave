//
// Created by Zhukov on 2020/7/23.
//

#ifndef MODBUSMASTER_FRAME_H
#define MODBUSMASTER_FRAME_H

int8_t frame_entry(uint8_t* rx_data, uint16_t rx_length, uint8_t* tx_data, uint16_t* tx_length);

#endif //MODBUSMASTER_FRAME_H
