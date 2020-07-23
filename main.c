#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "test/all_test.h"
#include "src/config.h"
#include "src/frame.h"
#include "src/frame_conversion.h"

void slave_rtu_mode_transmit()
{
    int8_t input_char[255];
    printf("the mode is RTU, so the frame template is 01030001000295CB\n");
    gets(input_char);
    size_t input_length = strlen(input_char);
    //printf("%d\n", input_length);
    uint8_t rx_data[255] = {0};
    uint16_t rx_length = 0;

    for (uint16_t i = 0; i < input_length; ++i)
    {
        rx_data[rx_length] = (char_to_number(input_char[i]) << 4) | char_to_number(input_char[i + 1]);
        i++;
        rx_length++;
    }
    uint8_t tx_data[255];
    uint16_t tx_length = 0;

    int8_t res = frame_entry(&rx_data[0], rx_length, &tx_data[0], &tx_length);
    if (res != 0)
    {
        int8_t output_char[255];
        uint16_t output_length = 0;

        for (uint16_t i = 0; i < tx_length; ++i)
        {
            output_char[output_length] = number_to_char(tx_data[i] >> 4);
            output_length++;
            output_char[output_length] = number_to_char(tx_data[i] & 0x0F);
            output_length++;
        }

        printf("%s\n", output_char);
    }
    else
    {
        printf("input error.\n");
    }
}

void slave_ascii_mode_transmit()
{
    int8_t input_char[255];
    printf("the mode is ASCII, so the frame template is :010300010002F9\n");
    gets(input_char);
    size_t input_length = strlen(input_char);
    //printf("%d\n", input_length);
    uint8_t rx_data[255] = {0};
    uint16_t rx_length = input_length;
    uint8_t tx_data[255];
    uint16_t tx_length = 0;

    int8_t res = frame_entry(&input_char[0], input_length, &tx_data[0], &tx_length);
    if (res != 0)
    {
/*
        int8_t output_char[255];
        uint16_t output_length = 0;
*/
        printf("%s\n", tx_data);
    }
    else
    {
        printf("input error.\n");
    }
}

int mainloop()
{
    printf("Please input the modbus frame:\n");

    if (slave_mode == RTU_MODE)
    {
        slave_rtu_mode_transmit();
    }
    else if (slave_mode == ASCII_MODE)
    {
        slave_ascii_mode_transmit();
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1],"test") == 0)
    {
        test_all();
    }
    else
    {
        printf("Please input mode:\n");
        printf("0:RTU  1:ASCII\n");
        printf("input:\n");
        char input_slave_mode[1];
        gets(input_slave_mode);
        slave_mode = atoi(input_slave_mode);

        while (1)
        {
            mainloop();
        }
    }
    return 0;
}

