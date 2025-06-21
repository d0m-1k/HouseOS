#include "vga.h"
#include "serial.h"
#include "idt.h"
#include "keyboard.h"
#include "multiboot.h"
#include "error.h"

void kernel_main(uint32_t magic, multiboot_info_t *mboot_info) {
	vga_clear_screen();
	init_serial();
	init_idt();
	init_keyboard();
	asm volatile("sti");

	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		make_kernel_panic("Error: Multiboot magic is unknown!");
		return;
	}

	vga_set_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	vga_put_string("Hello!\n");
	vga_put_hex(0xA0);

	serial_put_string("OS started\n");

	while (1);
}

