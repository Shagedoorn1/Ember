#include "heap.h"
#include "screen.h"  // for test/debug prints
#include <stdint.h>
#include <stddef.h>
#include "string.h"

#define HEAP_START 0x100000
#define HEAP_SIZE  0x10000

typedef struct Block {
    size_t size;
    struct Block* next;
    int free;
    // memory follows
} Block;

#define BLOCK_SIZE sizeof(Block)

static uint8_t* heap_base = (uint8_t*)HEAP_START;
static uint8_t* heap_end  = (uint8_t*)(HEAP_START + HEAP_SIZE);

static Block* head = NULL;

void* malloc(size_t size) {
    if (size == 0) return NULL;

    if (!head) {
        head = (Block*)heap_base;
        head->size = size;
        head->next = NULL;
        head->free = 0;
        return (void*)(head + 1);
    }

    Block* current = head;
    while (current) {
        if (current->free && current->size >= size) {
            current->free = 0;
            return (void*)(current + 1);
        }

        if (!current->next) break;
        current = current->next;
    }

    uint8_t* next_addr = (uint8_t*)current + BLOCK_SIZE + current->size;
    if (next_addr + BLOCK_SIZE + size > heap_end) {
        return NULL;
    }

    Block* new_block = (Block*)next_addr;
    new_block->size = size;
    new_block->free = 0;
    new_block->next = NULL;
    current->next = new_block;

    return (void*)(new_block + 1);
}

void free(void* ptr) {
    if (!ptr) return;
    Block* block = (Block*)ptr - 1;
    block->free = 1;
}

void* calloc(size_t num, size_t size) {
    size_t total = num * size;
    void* ptr = malloc(total);
    if (ptr) memset(ptr, 0, total);
    return ptr;
}

void *memset(void *dest, int val, size_t len) {
    unsigned char *ptr = dest;
    while (len-- > 0)
        *ptr++ = (unsigned char)val;
    return dest;
}

void *memcpy(void *dest, const void *src, size_t len) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    while (len--) 
        *d++ = *s++;
    return dest;
}

int memcmp(const void* s1, const void* s2, size_t n) {
    const unsigned char* a = s1;
    const unsigned char* b = s2;

    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return a[i] - b[i];
        }
    }
    return 0;
}

void* memmove(void* dest, const void* src, size_t n) {
    unsigned char* d = dest;
    const unsigned char* s = src;

    if (d == s) {
        return dest;
    }

    if (d < s) {
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else {
        for (size_t i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }

    return dest;
}