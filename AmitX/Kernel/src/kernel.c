#include "screen.h"
#include "io.h"
#include "interrupts.h"
#include "string.h"
#include "timer.h"   // ✅ Timer init
#include "time.h"    // ✅ sleep() and tick_count
#include <stdint.h>

extern void gdt_install();
extern void isr0();        // ISR for divide-by-zero
extern void isr32();       // ISR for PIT
extern void load_idt(uint32_t);

void draw_start() {
    screen_clear();
    screen_puts("Hello from the AmitX Kernel\n");
    draw_statusbar();
    screen_puts("\n");
}

struct IDTEntry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_hi;
} __attribute__((packed));

struct IDTPointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#define IDT_ENTRIES 256
struct IDTEntry idt[IDT_ENTRIES];
struct IDTPointer idt_ptr;

void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel     = sel;
    idt[num].always0 = 0;
    idt[num].flags   = flags;
}

void idt_install() {
    idt_ptr.limit = sizeof(struct IDTEntry) * IDT_ENTRIES - 1;
    idt_ptr.base = (uint32_t)&idt;

    idt_set_gate(0, (uint32_t)isr0,  0x08, 0x8E); // Divide-by-zero
    idt_set_gate(32, (uint32_t)isr32, 0x08, 0x8E); // Timer (IRQ0)

    load_idt((uint32_t)&idt_ptr);
}

void kernel_main(void) {
    draw_start();
    screen_puts("Installing GDT and IDT...\n");

    gdt_install();
    pic_remap();
    idt_install();

    screen_puts("Starting timer...\n");
    init_timer(100);  // 100Hz = 10ms interval
    
    screen_puts("Sleeping 2 seconds...\n");
    sleep(2);  // Wait ~200 ticks

    screen_puts("Done!\n");

    sleep(1);

    volatile int x = 1;
    volatile int y = 0;
    volatile int z = x / y;

    while (1);
}