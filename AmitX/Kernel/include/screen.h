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
void screen_puthex(uint32_t n);
void draw_menu(int pointer);
void screen_set_cursor(int x, int y);
void draw_uptime();
void screen_move_cursor(uint8_t x, uint8_t y);
void screen_get_cursor(uint8_t* x, uint8_t* y);

#endif
