#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void screen_clear();
void screen_putc(char c);
void screen_puts(const char* str);
void screen_setcolor(uint8_t fg, uint8_t bg);
void screen_newline();
void draw_statusbar(void);
void screen_putf(const char* str, uint8_t fg, uint8_t bg);
void screen_putint(int num);
void draw_menu(int pointer);

#endif
