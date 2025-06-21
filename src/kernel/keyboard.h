#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ports.h"
#include "vga.h"
#include "serial.h"

void init_keyboard();
void kernel_keyboard_handler();

#endif
