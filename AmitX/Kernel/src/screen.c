#include "screen.h"
#include "string.h"
#include "amitx_info.h"
#include "time.h"
#include "io.h"


#define VIDEO_ADDRESS 0xB8000
extern int tick_count;

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
static void update_hardware_cursor() {
    screen_set_cursor(cursor_col, cursor_row);
}

void screen_clear() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        video_memory[i] = (color << 8) | ' ';
    }
    cursor_row = 0;
    cursor_col = 0;
    update_hardware_cursor();
}

void screen_putc(char c) {
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
        scroll_if_needed();
        update_hardware_cursor();
        return;
    }
    if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
            video_memory[cursor_row * VGA_WIDTH + cursor_col] = (color << 8) | ' ';
            update_hardware_cursor();
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
    update_hardware_cursor();
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
    update_hardware_cursor();
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

void screen_putf(const char* str, uint8_t fg, uint8_t bg) {
    screen_setcolor(fg, bg);
    screen_puts(str);
    screen_puts("\n");
}

void screen_putint(int num) {
    char str[12];
    int_to_ascii(num, str);
    screen_puts(str);
}

void screen_puthex(uint32_t n) {
    screen_puts("0x");
    char hex_chars[] = "0123456789ABCDEF";
    int started = 0;
    for (int i = 7; i >= 0; i--) {
        uint8_t nibble = (n >> (i * 4)) & 0xF;
        if (nibble != 0 || started || i == 0) {
            screen_putc(hex_chars[nibble]);
            started = 1;
        }
    }
}

void draw_menu(int pointer) {
    if (pointer == 0) {
        screen_putf("Perch", 15, 0);
        screen_putf("Owly", 15, 0);
        screen_putf("Cyclone", 15, 0);
        screen_putf("Exit", 15, 0);
    } else if (pointer == 1) {
        screen_putf("Perch", 0, 15);
        screen_putf("Owly", 15, 0);
        screen_putf("Cyclone", 15, 0);
        screen_putf("Exit", 15, 0);
    } else if (pointer == 2) {
        screen_putf("Perch", 15, 0);
        screen_putf("Owly", 0, 15);
        screen_putf("Cyclone", 15, 0);
        screen_putf("Exit", 15, 0);
    } else if (pointer == 3){
        screen_putf("Perch", 15, 0);
        screen_putf("Owly", 15, 0);
        screen_putf("Cyclone", 0, 15);
        screen_putf("Exit", 15, 0);
    } else if (pointer == 4) {
        screen_putf("Perch", 15, 0);
        screen_putf("Owly", 15, 0);
        screen_putf("Cyclone", 15, 0);
        screen_putf("Exit", 0, 15);
    } else {
        screen_putf("Perch", 15, 0);
        screen_putf("Owly", 15, 0);
        screen_putf("Empty", 15, 0);
        screen_putf("Exit", 15, 0);
    }
    screen_setcolor(15, 0);
}

void screen_set_cursor(int x, int y) {
    uint16_t pos = y * VGA_WIDTH + x;

    // Send the high byte of the cursor location
    outb(0x3D4, 14);
    outb(0x3D5, (pos >> 8) & 0xFF);

    // Send the low byte of the cursor location
    outb(0x3D4, 15);
    outb(0x3D5, pos & 0xFF);
}

void draw_uptime() {
    uint8_t saved_x, saved_y;
    screen_get_cursor(&saved_x, &saved_y);

    int seconds = tick_count / 100;
    screen_move_cursor(0, 24);
    screen_puts("Uptime: ");
    screen_putint(seconds);
    screen_puts("s   ");

    screen_move_cursor(saved_x, saved_y);
}

void screen_move_cursor(uint8_t x, uint8_t y) {
    cursor_col = x;
    cursor_row = y;
    screen_set_cursor(x, y); // updates hardware too
}

void screen_get_cursor(uint8_t* x, uint8_t* y) {
    *x = cursor_col;
    *y = cursor_row;
}