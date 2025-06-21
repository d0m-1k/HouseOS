bits 32

section .text

multiboot:
	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 0x00)

global start
global write_port
global read_port
global idt_load
global keyboard_handler

extern kernel_main
extern kernel_keyboard_handler

start:
	cli
	mov esp, stack_space
	call kernel_main
	hlt

read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

write_port:
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	ret

idt_load:
	mov edx, [esp + 4]
	lidt [edx]
	ret

keyboard_handler:
	pushad
	call kernel_keyboard_handler
	popad
	iretd

section .bss

resb 8192
stack_space:
