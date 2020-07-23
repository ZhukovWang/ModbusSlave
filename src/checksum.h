//
// Created by Zhukov on 2020/7/23.
//

#ifndef MODBUSMASTER_CHECKSUM_H
#define MODBUSMASTER_CHECKSUM_H

uint8_t checksum_lrc(uint8_t* data, uint16_t length);
uint16_t checksum_crc(uint8_t* data, uint16_t length);

#endif //MODBUSMASTER_CHECKSUM_H
