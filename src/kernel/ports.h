#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

void write_port(uint16_t port, uint8_t value);
uint8_t read_port(uint16_t port);

#endif
