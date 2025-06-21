#include "idt.h"

struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idtp;

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
	idt[num].base_low = (base & 0xFFFF);
	idt[num].base_high = (base >> 16) & 0xFFFF;
	idt[num].selector = sel;
	idt[num].zero = 0;
	idt[num].flags = flags;
}

void init_idt() {
	idtp.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;
	idtp.base = (uint32_t)&idt;

	for (int i = 0; i < IDT_ENTRIES; i++) {
		idt_set_gate(i, 0, 0, 0);
	}

	idt_set_gate(0x21, (uint32_t)keyboard_handler, 0x08, 0x8E);

	idt_load((uint32_t)&idtp);
}
