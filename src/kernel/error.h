#ifndef ERROR_H
#define ERROR_H

#include "vga.h"
#include "kernel.h"

void make_kernel_panic(uint16_t error_code);
void make_kernel_panic_text();

#endif
