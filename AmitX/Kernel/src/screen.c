#include "screen.h"
#include "amitx_info.h"


#define VIDEO_ADDRESS 0xB8000

static uint16_t* const video_memory = (uint16_t*) VIDEO_ADDRESS;
static uint8_t cursor_row = 0;
static uint8_t cursor_col = 0;
static uint8_t color = 0x0F;  // default: white on black

static void scroll_if_needed() {
    if (cursor_row < VGA_HEIGHT - 1) return;

    // Scroll everything up one line
    for (int row = 1; row < VGA_HEIGHT - 1; row++) {
        for (int col = 0; col < VGA_WIDTH; col++) {
            video_memory[(row - 1) * VGA_WIDTH + col] = video_memory[row * VGA_WIDTH + col];
        }
    }
    // Clear last line
    for (int col = 0; col < VGA_WIDTH; col++) {
        video_memory[(VGA_HEIGHT - 1) * VGA_WIDTH + col] = (color << 8) | ' ';
    }
    cursor_row = VGA_HEIGHT - 1;
}

void screen_clear() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        video_memory[i] = (color << 8) | ' ';
    }
    cursor_row = 0;
    cursor_col = 0;
}

void screen_putc(char c) {
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
        scroll_if_needed();
        return;
    }
    if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
            video_memory[cursor_row * VGA_WIDTH + cursor_col] = (color << 8) | ' ';
        }
        return;
    }
    if (cursor_row >= VGA_HEIGHT - 1) {
        cursor_row = VGA_HEIGHT - 2;
        cursor_col = 0;
    }

    video_memory[cursor_row * VGA_WIDTH + cursor_col] = (color << 8) | c;
    cursor_col++;
    if (cursor_col >= VGA_WIDTH) {
        cursor_col = 0;
        cursor_row++;
        scroll_if_needed();
    }
}

void screen_puts(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        screen_putc(str[i]);
    }
}

void screen_setcolor(uint8_t fg, uint8_t bg) {
    color = (bg << 4) | (fg & 0x0F);
}

void screen_newline() {
    cursor_col = 0;
    cursor_row++;
    scroll_if_needed();
}

void draw_statusbar() {
    const char *name = AMITX_NAME;
    const char *version = AMITX_VERSION;
    const char *build_date = AMITX_BUILD_DATE;

    char status_text[80];
    int pos = 0;

    // Manually copy strings with spaces and parentheses, ensure no buffer overflow
    while (*name && pos < 79) status_text[pos++] = *name++;
    if (pos < 79) status_text[pos++] = ' ';
    while (*version && pos < 79) status_text[pos++] = *version++;
    if (pos < 79) status_text[pos++] = ' ';
    if (pos < 79) status_text[pos++] = '(';
    while (*build_date && pos < 79) status_text[pos++] = *build_date++;
    if (pos < 79) status_text[pos++] = ')';
    status_text[pos] = '\0';

    const uint8_t status_bg = 1;    // Blue background
    const uint8_t status_fg = 15;   // White foreground
    uint8_t status_color = (status_bg << 4) | (status_fg & 0x0F);

    // Clear last line
    for (int col = 0; col < VGA_WIDTH; col++) {
        video_memory[(VGA_HEIGHT - 1) * VGA_WIDTH + col] = (status_color << 8) | ' ';
    }

    // Write status text to last line
    for (int i = 0; i < pos && i < VGA_WIDTH; i++) {
        video_memory[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = (status_color << 8) | status_text[i];
    }
}