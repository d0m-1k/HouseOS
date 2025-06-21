#ifndef SERIAL_H
#define SERIAL_H

#include "ports.h"
#include "string.h"

#define COM1_PORT 0x3f8

void init_serial();
void serial_put_char(char c);
void serial_put_hex(uint8_t value);
void serial_put_dec(uint8_t value);
void serial_put_string(const char* str);

#endif
