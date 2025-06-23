#include "error.h"

void make_kernel_panic(uint16_t error_code) {
	make_kernel_panic_text();

	int len = 0;
	while (kernel_os_name[len] != '\0') len++;
	int x = (80 - len) / 2;
	if (x < 0) x = 0;

	vga_move_cursor(x, 6);
	vga_set_color(VGA_COLOR_BLUE, VGA_COLOR_LIGHT_GREY);
	vga_put_char(' ');
	vga_put_string(kernel_os_name);
	vga_put_char(' ');
	vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);

	vga_move_cursor(28, 8);
	vga_put_hex((error_code >> 8) & 0xFF);
	vga_put_hex(error_code & 0xFF);
}

void make_kernel_panic_text() {
	vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("        :(                                                                      ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("        A fatal exception 0x____ has occurred. The current application          ");
	vga_put_string("        will be terminated.                                                     ");
	vga_put_string("                                                                                ");
	vga_put_string("    *   Press any key to terminate the currnet application                      ");
	vga_put_string("    *   Press CTRL+ALT+DEL again to restart your computer. You will             ");
	vga_put_string("        lose any unsaved information in all applications.                       ");
	vga_put_string("                                                                                ");
	vga_put_string("                           Press any key to continue                            ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
	vga_put_string("                                                                                ");
}
