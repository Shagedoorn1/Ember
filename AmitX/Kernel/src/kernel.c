#include "screen.h"
#include "io.h"
#include "string.h"
#include "timer.h"   // ✅ Timer init
#include "time.h"    // ✅ sleep() and tick_count
#include "keyboard.h"
#include "interrupts.h"
#include "idt.h"
#include <stdint.h>


extern void gdt_install();
extern POINTER;

void kernel_setup() {
    gdt_install();
    pic_remap();
    idt_install();
    init_keyboard();
    init_timer(100);
}

void draw_start() {
    screen_clear();
    screen_puts("Hello from the AmitX Kernel\n");
    draw_statusbar();
    screen_puts("\n");
    draw_menu(POINTER);
}
void kernel_main(void) {
    kernel_setup();
    draw_start();
    while (1);
}