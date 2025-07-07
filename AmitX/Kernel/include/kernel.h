#ifndef KERNEL_H
#define KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

void kernel_main(void);
void draw_start(void);
void trigger_divide_by_zero(void);
volatile int zero = 0;
int i = 1 / zero;

#ifdef __cplusplus
}
#endif

#endif
