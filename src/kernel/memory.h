#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>
#include "multiboot.h"

#define PAGE_SIZE 4096
#define KERNEL_VIRT_BASE 0xC0000000

typedef struct {
	uint32_t total_pages;
	uint32_t used_pages;
	uint8_t* bitmap;
	uint32_t bitmap_size;
} phys_mem_manager_t;

void init_memory(void* mboot_ptr);
void* alloc_page();
void free_page(void* addr);
void* memset(void* ptr, uint8_t value, uint32_t size);
void* memcpy(void* dest, const void* src, size_t n);
void init_virtual_memory();
void map_page(void* virt, void* phys, uint32_t flags);
void* valloc(size_t size);
void vfree(void* addr, size_t size);

#endif
