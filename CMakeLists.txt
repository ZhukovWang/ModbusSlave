cmake_minimum_required(VERSION 3.16)
project(ModbusSlave)

set(CMAKE_C_STANDARD 11)

add_executable(ModbusSlave
        main.c
        test/unity.c
        test/unity.c
        test/unity_internals.h
        src/checksum.c
        src/checksum.h
        test/checksum_test.c
        test/checksum_test.h
        test/all_test.c
        test/all_test.h
        src/modbus.c
        src/modbus.h
        test/modbus_test.c
        test/modbus_test.h src/register.c src/register.h src/config.c src/config.h src/frame_conversion.c src/frame_conversion.h test/frame_conversion_test.c test/frame_conversion_test.h src/frame.c src/frame.h test/frame_test.c test/frame_test.h)
