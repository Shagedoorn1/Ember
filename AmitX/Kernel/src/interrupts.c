#include "screen.h"

void isr0_handler() {
    screen_setcolor(0, 15);
    screen_puts("[ERRNO-0]: Zero-division\n");
    while (1) {}
}