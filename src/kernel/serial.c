#include "serial.h"

void init_serial() {
	write_port(COM1_PORT + 1, 0x00); // Отключаем прерывания
	write_port(COM1_PORT + 3, 0x80); // Включаем DLAB
	write_port(COM1_PORT + 0, 0x03); // Устанавливаем скорость 38400 baud
	write_port(COM1_PORT + 1, 0x00);
	write_port(COM1_PORT + 3, 0x03); // 8 бит, no parity, one stop bit
	write_port(COM1_PORT + 2, 0xC7); // Включаем FIFO
}

void serial_put_char(char c) {
	while ((read_port(COM1_PORT + 5) & 0x20) == 0);
	write_port(COM1_PORT, c);
}

void serial_put_hex(uint8_t value) {
	char hex[] = "0123456789ABCDEF";
	serial_put_char(hex[value >> 4]);
	serial_put_char(hex[value & 0x0F]);
}

void serial_put_dec(uint8_t value) {
	if (value >= 100) serial_put_char('0' + value / 100);
	if (value >= 10) serial_put_char('0' + (value / 10) % 10);
	serial_put_char('0' + value % 10);
}

void serial_put_string(const char* str) {
	while (*str) {
		serial_put_char(*str++);
	}
}
