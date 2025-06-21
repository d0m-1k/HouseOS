#include "error.h"


void make_kernel_panic(char* text) {
	vga_set_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
	vga_put_char('\n');
	for (int i = 0; i < 33; i++) vga_put_char('=');
	vga_put_string(" KERNEL PANIC ");
	for (int i = 0; i < 33; i++) vga_put_char('=');
	vga_put_string(text);
	vga_put_char('\n');
	for (int i = 0; i < 33; i++) vga_put_char('=');
	vga_put_string(" KERNEL PANIC ");
	for (int i = 0; i < 33; i++) vga_put_char('=');
	vga_put_char('\n');
	vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}
