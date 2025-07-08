#include "screen.h"
#include "io.h"
#include <stdint.h>

#define MAX_INTERRUPTS 256

void (*interrupt_handlers[MAX_INTERRUPTS])();

void register_interrupt_handler(int n, void (*handler)()) {
    interrupt_handlers[n] = handler;
}

// Called from isr_stub.S
void isr_handler(int interrupt_number) {
    if (interrupt_handlers[interrupt_number]) {
        interrupt_handlers[interrupt_number]();
    }

    if (interrupt_number >= 40) {
        // If the interrupt came from the slave PIC
        outb(0xA0, 0x20);
    }
    if (interrupt_number >= 32) {
        outb(0x20, 0x20);
    }

}

void isr0_handler() {
    screen_setcolor(0, 15);
    screen_puts("[ERRNO-0]: Zero-division\n");
    while (1) {}
}

void pic_remap() {
    // Start initialization
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    // Set new vector offsets
    outb(0x21, 0x20);  // Master PIC: 0x20–0x27
    outb(0xA1, 0x28);  // Slave PIC: 0x28–0x2F

    // Tell Master PIC there is a slave PIC at IRQ2 (0000 0100)
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    // Set mode
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // Enable all IRQs again (unmask)
    outb(0x21, 0x00);
    outb(0xA1, 0x00);

    screen_puts("Remap complete\n");
}