#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>
#include "multiboot.h"

#define PAGE_SIZE 4096
#define BITMAP_SIZE 32768

typedef struct {
	uint32_t total_pages;
	uint32_t used_pages;
	uint8_t *bitmap;
	uint32_t bitmap_size;
} phys_mem_manager_t;

extern phys_mem_manager_t pm_manager;

void init_memory(void *mboot_info);
void *alloc_page();
void free_page(void *addr);
void memset(void *ptr, uint8_t value, uint32_t size);
void* memcpy(void* dest, const void* src, size_t n);

#endif
