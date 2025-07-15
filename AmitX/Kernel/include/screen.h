#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void clear();
void putc(char c);
void setcolor(uint8_t fg, uint8_t bg);
void newline();
void draw_uptime();
void draw_statusbar(void);
void draw_menu(int pointer);
void puts(const char* str);
void blink();
void putf(const char* str, uint8_t fg, uint8_t bg);
void putint(int num);
void puthex(uint32_t n);
void set_cursor(int x, int y);
void move_cursor(uint8_t x, uint8_t y);
void get_cursor(uint8_t* x, uint8_t* y);

#endif
