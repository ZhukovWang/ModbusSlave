cmake_minimum_required(VERSION 3.16)
project(ModbusMaster)

set(CMAKE_C_STANDARD 11)

add_executable(ModbusMaster
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
        test/modbus_test.h src/register.c src/register.h src/config.c src/config.h)
