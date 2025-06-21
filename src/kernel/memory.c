#include "memory.h"

phys_mem_manager_t pm_manager;

void memset(void *ptr, uint8_t value, uint32_t size) {
	uint8_t *p = (uint8_t*)ptr;
	for(uint32_t i = 0; i < size; i++)
		p[i] = value;
}

void init_memory(void *mboot_ptr) {
	multiboot_info_t *mboot_info = (multiboot_info_t*)mboot_ptr;

	if(!(mboot_info->flags & (1<<6))) {
		pm_manager.total_pages = (1024 * 1024 * 16) / PAGE_SIZE;
		pm_manager.used_pages = 0;
		pm_manager.bitmap = (uint8_t*)0x200000;
		pm_manager.bitmap_size = (pm_manager.total_pages + 7) / 8;
		memset(pm_manager.bitmap, 0xFF, pm_manager.bitmap_size);
		return;
	}

	multiboot_memory_map_t *mmap = (multiboot_memory_map_t*)mboot_info->mmap_addr;
	uint32_t total_mem = 0;

	while((uint32_t)mmap < mboot_info->mmap_addr + mboot_info->mmap_length) {
		if(mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
			total_mem += mmap->len;
		}
		mmap = (multiboot_memory_map_t*)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
	}

	pm_manager.total_pages = total_mem / PAGE_SIZE;
	pm_manager.used_pages = pm_manager.total_pages;
	pm_manager.bitmap = (uint8_t*)0x200000;
	pm_manager.bitmap_size = (pm_manager.total_pages + 7) / 8;

	memset(pm_manager.bitmap, 0xFF, pm_manager.bitmap_size);

	mmap = (multiboot_memory_map_t*)mboot_info->mmap_addr;
	while((uint32_t)mmap < mboot_info->mmap_addr + mboot_info->mmap_length) {
		if(mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
			uint32_t start_page = mmap->addr / PAGE_SIZE;
			uint32_t end_page = (mmap->addr + mmap->len) / PAGE_SIZE;
			for(uint32_t i = start_page; i < end_page; i++) {
				pm_manager.bitmap[i / 8] &= ~(1 << (i % 8));
				pm_manager.used_pages--;
			}
		}
		mmap = (multiboot_memory_map_t*)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
	}

	uint32_t bitmap_start_page = (uint32_t)pm_manager.bitmap / PAGE_SIZE;
	uint32_t bitmap_end_page = (bitmap_start_page + pm_manager.bitmap_size + PAGE_SIZE - 1) / PAGE_SIZE;
	for(uint32_t i = bitmap_start_page; i < bitmap_end_page; i++) {
		pm_manager.bitmap[i / 8] |= (1 << (i % 8));
		pm_manager.used_pages++;
	}
}

void *alloc_page() {
	for(uint32_t i = 0; i < pm_manager.total_pages; i++) {
		if(!(pm_manager.bitmap[i / 8] & (1 << (i % 8)))) {
			pm_manager.bitmap[i / 8] |= (1 << (i % 8));
			pm_manager.used_pages++;
			void *page = (void*)(i * PAGE_SIZE);
			memset(page, 0, PAGE_SIZE);
			return page;
		}
	}
	return 0;
}

void free_page(void *addr) {
	uint32_t page_index = (uint32_t)addr / PAGE_SIZE;
	if(page_index >= pm_manager.total_pages) return;

	if(pm_manager.bitmap[page_index / 8] & (1 << (page_index % 8))) {
		pm_manager.bitmap[page_index / 8] &= ~(1 << (page_index % 8));
		pm_manager.used_pages--;
	}
}

void* memcpy(void* dest, const void* src, size_t n) {
	char* d = dest;
	const char* s = src;
	for (size_t i = 0; i < n; i++) {
		d[i] = s[i];
	}
	return dest;
}
