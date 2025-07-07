.intel_syntax noprefix
.global isr0
.global load_idt

.extern isr0_handler

isr0:
    cli         # Disable interrupts
    pusha       # Save general-purpose registers

    call isr0_handler  # Call the C handler

    popa        # Restore registers
    sti         # Re-enable interrupts
    iret        # Return from interrupt

load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret