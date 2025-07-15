#include "Paging/paging.h"
#include "screen.h"
#include "heap.h"
#include "string.h"

#define PAGE_DIRECTORY_SIZE 1024
#define PAGE_TABLE_SIZE     1024

static uint32_t page_directory[PAGE_DIRECTORY_SIZE] __attribute__((aligned(4096)));
static uint32_t first_page_table[PAGE_TABLE_SIZE] __attribute__((aligned(4096)));

void paging_init() {
    puts("[paging] Initializing paging...\n");

    // Identity map first 4MB using the first page table
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        first_page_table[i] = (i * PAGE_SIZE) | PAGE_PRESENT | PAGE_RW;
    }

    page_directory[0] = ((uint32_t)first_page_table) | PAGE_PRESENT | PAGE_RW;

    // Clear the rest of the directory
    for (int i = 1; i < PAGE_DIRECTORY_SIZE; i++) {
        page_directory[i] = 0;
    }

    load_page_directory(page_directory);
    enable_paging();

    puts("[paging] Paging is now active!\n");
}

void load_page_directory(uint32_t* pd) {
    asm volatile("mov %0, %%cr3" :: "r"(pd) : "memory");
}

void enable_paging() {
    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; // Set PG bit
    asm volatile("mov %0, %%cr0" :: "r"(cr0));
}

void flush_tlb() {
    uint32_t cr3;
    asm volatile("mov %%cr3, %0" : "=r"(cr3));
    asm volatile("mov %0, %%cr3" :: "r"(cr3) : "memory");
}

void map_page(uint32_t phys_addr, uint32_t virt_addr, uint32_t flags) {
    uint32_t pd_index = virt_addr >> 22;
    uint32_t pt_index = (virt_addr >> 12) & 0x03FF;

    uint32_t* page_table;

    // Allocate a new page table if needed
    if (!(page_directory[pd_index] & PAGE_PRESENT)) {
        page_table = (uint32_t*)malloc(PAGE_SIZE);
        if (!page_table) {
            puts("[map_page] ERROR: malloc failed\n");
            while (1);
        }

        memset(page_table, 0, PAGE_SIZE);
        page_directory[pd_index] = ((uint32_t)page_table) | PAGE_PRESENT | PAGE_RW;
    } else {
        page_table = (uint32_t*)(page_directory[pd_index] & 0xFFFFF000);
    }

    // Map the physical address
    page_table[pt_index] = (phys_addr & 0xFFFFF000) | flags | PAGE_PRESENT;
    flush_tlb();
}

uint32_t get_phys_addr(uint32_t virt_addr) {
    uint32_t pd_index = virt_addr >> 22;
    uint32_t pt_index = (virt_addr >> 12) & 0x03FF;

    if (!(page_directory[pd_index] & PAGE_PRESENT)) return 0;

    uint32_t* page_table = (uint32_t*)(page_directory[pd_index] & 0xFFFFF000);
    if (!(page_table[pt_index] & PAGE_PRESENT)) return 0;

    uint32_t phys = page_table[pt_index] & 0xFFFFF000;
    return phys + (virt_addr & 0xFFF);
}