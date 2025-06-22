#include "vga.h"
#include "serial.h"
#include "idt.h"
#include "keyboard.h"
#include "multiboot.h"
#include "error.h"
#include "memory.h"

void kernel_main(uint32_t magic, multiboot_info_t* mboot_info) {
	vga_clear_screen();
	init_serial();

	init_memory(mboot_info);
	init_virtual_memory();

	init_idt();
	init_keyboard();
	asm volatile("sti");

	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		make_kernel_panic("Error: Multiboot magic is unknown!");
		return;
	}

	vga_put_string("HouseOS v1.0\n");
	serial_put_string("HouseOS v1.0\n");

	while (1);
}

