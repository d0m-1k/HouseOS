#include "vga.h"
#include "serial.h"
#include "idt.h"
#include "keyboard.h"

void kernel_main() {
	vga_clear_screen();
	vga_set_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	vga_put_string("Hello!\n");

	vga_put_hex(0xA0);

	serial_init();
	serial_put_string("OS started\n");

	init_idt();
	init_keyboard();
	asm volatile("sti");

	while (1);
}
