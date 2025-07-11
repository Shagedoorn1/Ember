#ifndef AMITC_H
#define AMITC_H

void syscall(int num, void* arg1, void* arg2, void* arg3);

void sys_write(const char* str);
int  sys_time();
void sys_clear();
void sys_cursor(int x, int y);
void sys_draw_logo();
char sys_getchar();
void sys_putchar(char c);
void sys_sleep(int ticks);

#endif