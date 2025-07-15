#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

#define PAGE_PRESENT 0x1
#define PAGE_RW      0x2
#define PAGE_USER    0x4
#define PAGE_SIZE    4096

void paging_init();
void enable_paging();
void load_page_directory(uint32_t* pd);
uint32_t get_phys_addr(uint32_t virt_addr);
void map_page(uint32_t phys_addr, uint32_t virt_addr, uint32_t flags);
void testp();

#endif