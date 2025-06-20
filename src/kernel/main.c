#include "vga.h"

void kernel_main() {
	vga_clear_screen();

	vga_set_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	vga_put_string("Hello!");

	while (1);
}
