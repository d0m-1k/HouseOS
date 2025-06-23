#ifndef ERROR_H
#define ERROR_H

#include "vga.h"
#include "kernel.h"

void make_kernel_panic(uint8_t error_code, uint16_t segment, uint32_t offset);
void make_kernel_panic_text();

#endif
