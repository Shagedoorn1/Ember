#include "screen.h"
#include "io.h"
#include "string.h"
#include <stdint.h>

extern void gdt_install();

void draw_start() {
    screen_clear();
    screen_puts("Hello from the AmitX\nkernel\n");
    draw_statusbar();
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

extern void isr0(); // From interrupts.S
extern void load_idt(uint32_t);

void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel     = sel;
    idt[num].always0 = 0;
    idt[num].flags   = flags;
}

extern void load_idt(uint32_t);

void idt_install() {
    idt_ptr.limit = sizeof(struct IDTEntry) * IDT_ENTRIES - 1;
    idt_ptr.base = (uint32_t)&idt;

    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);

    load_idt((uint32_t)&idt_ptr);
}

void trigger_divide_by_zero() {
    volatile int a = 1;
    volatile int b = 0;
    volatile int c;
    c = a / b;  // should cause interrupt 0
}

void kernel_main(void) {
    screen_clear();
    screen_puts("Setting up GDT...\n");

    gdt_install();

    screen_puts("Setting up IDT...\n");

    idt_install();

    screen_puts("Triggering division by zero...\n");
    trigger_divide_by_zero();

    while (1);
}
