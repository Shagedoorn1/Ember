#include "kernel.h"
#include "screen.h"

void kernel_main(void) {
    clear_screen();
    print_string("Hello from AmitX kernel!\n");
    for (;;);
}
