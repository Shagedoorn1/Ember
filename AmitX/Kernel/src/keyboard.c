#include "keyboard.h"
#include "io.h"
#include "screen.h"
#include "kernel.h"
#include "interrupts.h"
#include <stdint.h>

int POINTER = 0;

static const char scancode_map[] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=','\b', // Backspace
    '\t', // Tab
    'q','w','e','r','t','y','u','i','o','p','[',']','\n',         // Enter
    0,    // Control
    'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,    // Left shift
    '\\','z','x','c','v','b','n','m',',','.','/',
    0,    // Right shift
    '*',
    0,    // Alt
    ' ',  // Spacebar
    0,    // Caps lock
    // And so on...
};

void keyboard_callback() {
    uint8_t scancode = inb(0x60);

    if (scancode < sizeof(scancode_map)) {
        char c = scancode_map[scancode];
        if (c) {
            char str[2] = {c, '\0'};
            if (c == 's') {
                if (POINTER < 3) {
                POINTER++;
                }
                draw_start();
            } else if (c == 'w') {
                if (POINTER > 0) {
                    POINTER--;
                    draw_start();
                }
            }
        }
    }
}

void init_keyboard() {
    register_interrupt_handler(33, keyboard_callback); // IRQ1
    __asm__ __volatile__ ("sti");
}