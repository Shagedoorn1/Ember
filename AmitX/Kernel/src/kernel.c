#include "screen.h"
#include "io.h"
#include "string.h"
#include "timer.h"   // ✅ Timer init
#include "time.h"    // ✅ sleep() and tick_count
#include "keyboard.h"
#include "interrupts.h"
#include "idt.h"
#include "amitc.h"
#include "fs.h"
#include "cyclone.h"
#include <stdint.h>

int menu = 0;

extern void gdt_install();
extern int POINTER;
extern int load_cyclone;

void qemu_exit(int code) {
    outb(0xF4, code);
}

void launch_app(int app_code) {
    outb(0xF4, 0x10 + app_code);  // e.g., 0x11 = Perch, 0x12 = Owly
}

void kernel_setup() {
    gdt_install();
    pic_remap();
    idt_install();
    init_keyboard();
    init_timer(100);
    fs_init();
    screen_clear();
}

void draw_start() {
    kernel_setup();
    screen_puts("Hello from the AmitX Kernel\n");
    draw_statusbar();
    screen_puts("\n");
    draw_menu(POINTER);
    menu = 1;
    if (load_cyclone) {
        cyclone_main(1);
    }
}

void test_fs() {
    fs_init();
    fs_debug_list();

    const char* content = fs_read("/Saved/hello.txt");
    if (content) {
        screen_puts("\nContent of hello.txt:\n");
        screen_puts(content);
    } else {
        screen_puts("File not found.\n");
    }
    screen_newline();
    const char* content2 = fs_read("/Saved/log.txt");
    if (content2) {
        screen_puts("\nContent of log.txt:\n");
        screen_puts(content2);
    } else {
        screen_puts("File not found.\n");
    }
    screen_newline();
    const char* content3 = fs_read("/Saved/me.txt");
    if (content3) {
        screen_puts("\nContent of me.txt:\n");
        screen_puts(content3);
    } else {
        screen_puts("File not found.\n");
    }
}

void kernel_main(void) {
    kernel_setup();
    draw_start();

    
    while (1){

    }
}