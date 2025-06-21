#include "keyboard.h"

static const char keymap[128] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
};

void init_keyboard() {
	write_port(0x20, 0x11);
	write_port(0x21, 0x20);
	write_port(0x21, 0x04);
	write_port(0x21, 0x01);
	write_port(0x21, 0xFD);
}

void kernel_keyboard_handler() {
	uint8_t scancode = read_port(0x60);
	if (scancode < 128) {
		char c = keymap[scancode];
		if (c) {
			vga_put_char(c);
			serial_put_char(c);
		}
	}
	write_port(0x20, 0x20);
}
