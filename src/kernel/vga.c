#include "vga.h"

volatile char* vga = (volatile char*)0xB8000;
int cursor_x = 0;
int cursor_y = 0;
uint8_t text_color = VGA_COLOR_WHITE;
uint8_t bg_color = VGA_COLOR_BLACK;

void vga_set_color(uint8_t fg, uint8_t bg) {
	text_color = fg;
	bg_color = bg;
}

uint8_t vga_get_attribute() {
	return (bg_color << 4) | (text_color & 0x0F);
}

void vga_clear_screen() {
	uint8_t attr = vga_get_attribute();
	for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		vga[i * 2] = ' ';
		vga[i * 2 + 1] = attr;
	}
	cursor_x = 0;
	cursor_y = 0;
}

void vga_move_cursor(int x, int y) {
	cursor_x = x;
	cursor_y = y;
	if (cursor_x >= VGA_WIDTH) {
		cursor_x = 0;
		cursor_y++;
	}
	if (cursor_y >= VGA_HEIGHT) {
		cursor_y = 0;
	}
}

void vga_scroll() {
	uint8_t attr = vga_get_attribute();
	for (int y = 1; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			int from = (y * VGA_WIDTH + x) * 2;
			int to = ((y - 1) * VGA_WIDTH + x) * 2;
			vga[to] = vga[from];
			vga[to + 1] = vga[from + 1];
		}
	}
	for (int x = 0; x < VGA_WIDTH; x++) {
		int pos = ((VGA_HEIGHT - 1) * VGA_WIDTH + x) * 2;
		vga[pos] = ' ';
		vga[pos + 1] = attr;
	}
	cursor_y = VGA_HEIGHT - 1;
	cursor_x = 0;
}

void vga_put_char(char c) {
	if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	} else if (c == '\r') {
		cursor_x = 0;
	} else if (c == '\t') {
		cursor_x = (cursor_x + 4) & ~3;
	} else if (c >= ' ') {
		int pos = (cursor_y * VGA_WIDTH + cursor_x) * 2;
		vga[pos] = c;
		vga[pos + 1] = vga_get_attribute();
		cursor_x++;
	}
	if (cursor_x >= VGA_WIDTH) {
		cursor_x = 0;
		cursor_y++;
	}
	if (cursor_y >= VGA_HEIGHT) {
		vga_scroll();
	}
}

void vga_put_string(const char* str) {
	while (*str) {
		vga_put_char(*str++);
	}
}

void vga_put_hex(uint8_t value) {
	char hex[] = "0123456789ABCDEF";
	vga_put_char(hex[value >> 4]);
	vga_put_char(hex[value & 0x0F]);
}

void vga_put_dec(uint8_t value) {
	if (value >= 100) vga_put_char('0' + value / 100);
	if (value >= 10) vga_put_char('0' + (value / 10) % 10);
	vga_put_char('0' + value % 10);
}
