#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

void* malloc(size_t size);
void free(void* ptr);  // Optional if you plan to implement it
void* calloc(size_t num, size_t size);
void *memset(void *dest, int val, size_t len);
void *memcpy(void *dest, const void *src, size_t len);
int memcmp(const void* s1, const void* s2, size_t n);
void* memmove(void* dest, const void* src, size_t n);

#endif
