.intel_syntax noprefix
.global isr0
.global load_idt
.global isr32
.global isr33

.extern isr0_handler
.extern isr_handler

isr0:
    cli         # Disable interrupts
    pusha       # Save general-purpose registers

    call isr0_handler  # Call the C handler

    popa        # Restore registers
    sti         # Re-enable interrupts
    iret        # Return from interrupt

isr32:
    pusha
    push 32
    call isr_handler
    add esp, 4
    popa
    iret

isr33:
    pusha
    push 33
    call isr_handler
    add esp, 4
    popa
    iret
    
load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret