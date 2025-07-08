#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1
#define ICW1_INIT    0x10
#define ICW1_ICW4    0x01
#define ICW4_8086    0x01

void pic_remap() {
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC1_DATA, 0x20); // Master offset: IRQs start at 0x20 (32)
    outb(PIC2_DATA, 0x28); // Slave offset: IRQs start at 0x28 (40)
    outb(PIC1_DATA, 4);    // Tell Master PIC that there is a slave PIC at IRQ2
    outb(PIC2_DATA, 2);    // Tell Slave PIC its cascade identity
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    // Optionally, unmask all interrupts
    outb(PIC1_DATA, 0x0);
    outb(PIC2_DATA, 0x0);
}
