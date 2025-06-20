#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define VGA_WIDTH	80
#define VGA_HEIGHT	25

#define VGA_COLOR_BLACK		0
#define VGA_COLOR_BLUE		1
#define VGA_COLOR_GREEN		2
#define VGA_COLOR_CYAN		3
#define VGA_COLOR_RED		4
#define VGA_COLOR_MAGENTA	5
#define VGA_COLOR_BROWN		6
#define VGA_COLOR_LIGHT_GREY	7
#define VGA_COLOR_DARK_GREY	8
#define VGA_COLOR_LIGHT_BLUE	9
#define VGA_COLOR_LIGHT_GREEN	10
#define VGA_COLOR_LIGHT_CYAN	11
#define VGA_COLOR_LIGHT_RED	12
#define VGA_COLOR_LIGHT_MAGENTA	13
#define VGA_COLOR_YELLOW	14
#define VGA_COLOR_WHITE		15

extern volatile char* vga;
extern int cursor_x;
extern int cursor_y;

void vga_set_color(uint8_t fg, uint8_t bg);
void vga_clear_screen(void);
void vga_move_cursor(int x, int y);
void vga_put_char(char c);
void vga_put_string(const char* str);

#endif
