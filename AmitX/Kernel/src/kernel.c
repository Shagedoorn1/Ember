#include "screen.h"
#include "Paging/paging.h"
#include "io.h"
#include "string.h"
#include "timer.h"   // ✅ Timer init
#include "time.h"    // ✅ sleep() and tick_count
#include "keyboard.h"
#include "interrupts.h"
#include "idt.h"
#include "amitc.h"
#include "heap.h"
#include "fs.h"
#include "task.h"
#include "commands.h"
#include "app.h"
#include "cyclone.h"
#include <stdint.h>

int menu = 0;

const char* main_menu[] = {
    "Perch",
    "Owly",
    "Cyclone",
    "Exit",
    "Extra 1"
};
const int main_menu_count = sizeof(main_menu) / sizeof(main_menu[0]);

extern void gdt_install();
extern int POINTER;
extern int load_cyclone;
int owly;


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
    paging_init();
    init_tasks();
    clear();
}

void draw_start() {
    move_cursor(0,0);
    puts("Hello from the AmitX Kernel\n");
    draw_statusbar();
    puts("\n");
    draw_list(0, 2, 20, 7, main_menu, main_menu_count, POINTER);


    menu = 1;

    if (load_cyclone) {
        puts("loading cyclone");
        cyclone_main(1);
    }
}

void kernel_main(void) {
    kernel_setup();
    draw_start();

    while (1){
    }
}