#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

void *memset(void *dest, int val, size_t len);
void *memcpy(void *dest, const void *src, size_t len);
void int_to_ascii(int n, char str[]);
int strcmp(const char* s1, const char* s2);
uint32_t atoi(const char* str);
char* strcat(char* dest, const char* src);
char* strcpy(char* dest, const char* src);
char* strchr(const char* srt, int c);
char* strdup(const char* str);
size_t strlen(const char* str);
void* malloc(size_t size);
#endif
