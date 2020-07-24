# ModbusSlave

ModbusSlave is a modbus slave libary. 

Build by standard C11 and can be used in Windows/Linux/embedded. 

Had been tested in Windows (msys gcc 9.3) and Linux (Ubuntu 18.04 gcc 7.5).

Support ascii and rtu mode. Can be used in serial or tcp.

## Support Function code

- [x] 0x01
- [x] 0x03
- [x] 0x05
- [x] 0x06
- [x] 0x0F
- [x] 0x10

## Build

Use [Cmake](https://github.com/Kitware/CMake) to build.

The unit testing suits is [Unity](https://github.com/ThrowTheSwitch/Unity).

## Usage

The libary main function is `frame_entry()` in `src/frame.c`.

Test the libary:

```bash
$ ModbusSlave
```

Unit test the libary:

```bash
$ ModbusSlave test
```

## LICENSE

MIT
