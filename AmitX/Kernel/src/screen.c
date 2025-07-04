#include <stdint.h>
#include "screen.h"

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

uint16_t* video_memory = (uint16_t*) VIDEO_ADDRESS;
int cursor_row = 0;
int cursor_col = 0;

void clear_screen() {
    for (int i = 0; i < MAX_ROWS * MAX_COLS; i++) {
        video_memory[i] = (WHITE_ON_BLACK << 8) | ' ';
    }
    cursor_row = 0;
    cursor_col = 0;
}

void print_char(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else {
        int index = cursor_row * MAX_COLS + cursor_col;
        video_memory[index] = (WHITE_ON_BLACK << 8) | c;
        cursor_col++;
        if (cursor_col >= MAX_COLS) {
            cursor_col = 0;
            cursor_row++;
        }
    }

    // Optional: scroll screen or stop writing if out of bounds
    if (cursor_row >= MAX_ROWS) {
        cursor_row = 0;
    }
}

void print_string(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        print_char(str[i]);
    }
}
