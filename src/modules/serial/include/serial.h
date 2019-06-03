#pragma once
#include <stdint.h>

// Base addresses.

#define COM1                0x3F8
#define COM2                0x2F8
#define COM3                0x3E8
#define COM4                0x2E8
#define SERIAL_DLAB         0x80

#define SERIAL_DATA(base)           (base)
#define SERIAL_INTERRUPT(base)      (base + 1)
#define SERIAL_FIFO_COMMAND(base)   (base + 2)
#define SERIAL_LINE_COMMAND(base)   (base + 3)
#define SERIAL_MODEM_COMMAND(base)  (base + 4)
#define SERIAL_LINE_STATUS(base)    (base + 5)

void serialinit(uint16_t port, uint16_t divisor);
char read_serial();
uint8_t serialready();
void write_serial(char c);
