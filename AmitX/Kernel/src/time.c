#include "time.h"
#include "timer.h"
#include "screen.h"
#include <stdint.h>

volatile uint32_t tick_count = 0;

void timer_callback() {
    tick_count++;

}
void sleep(uint32_t seconds) {
    uint32_t start = tick_count;
    while ((tick_count - start) < (seconds * 100)) {
        // 18.2 Hz by default if PIT isn't configured.
        // Replace 18 with real frequency if configured.
    }
}