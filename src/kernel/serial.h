#ifndef SERIAL_H
#define SERIAL_H

#include "ports.h"

#define COM1_PORT 0x3f8

void serial_init();
void serial_put_char(char c);
void serial_put_string(const char* str);

#endif
