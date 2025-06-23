#include "kernel.h"

#include "vga.h"
#include "serial.h"
#include "idt.h"
#include "keyboard.h"
#include "multiboot.h"
#include "error.h"
#include "memory.h"

char* kernel_os_name = "HouseOS";
char* kernel_os_version = "v1.1";

void kernel_main(uint32_t magic, multiboot_info_t* mboot_info) {
	vga_clear_screen();
	init_serial();

	init_memory(mboot_info);
	init_virtual_memory();

	init_idt();
	init_keyboard();
	asm volatile("sti");

	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		make_kernel_panic(0x3000);
		return;
	}

	vga_put_string(kernel_os_name);
	vga_put_char(' ');
	vga_put_string(kernel_os_version);
	vga_put_char('\n');

	serial_put_string(kernel_os_name);
	serial_put_char(' ');
	serial_put_string(kernel_os_version);
	serial_put_char('\n');

	while (1);
}

