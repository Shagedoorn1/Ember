#include "screen.h"
#include "time.h"
#include "logo.h"
#include "keyboard.h"
#include "syscall.h"

extern int tick_count;

void syscall(int num, void* arg1, void* arg2) {
    switch (num) {
        case SYSCALL_WRITE:
            puts((const char*)arg1);
            break;
        case SYSCALL_TIME:
            *(int*)arg1 = tick_count;
            break;
        case SYSCALL_CLEAR:
            clear();
            break;
        case SYSCALL_CURSOR:
            move_cursor((int)(uintptr_t)arg1, (int)(uintptr_t)arg2);
            break;
        case SYSCALL_DRAW_LOGO:
            draw_logo((int)arg1);
            break;
        case SYSCALL_GETCHAR:
            *(char*)arg1 = keyboard_getchar();
            break;
        case SYSCALL_PUTCHAR:
            putc((char)(uintptr_t)arg1);
            break;
        case SYSCALL_SLEEP: {
            int seconds = (int)(uintptr_t)arg1;
            sleep(seconds);
            break;
        }
        default:
            puts("Unknown syscall\n");
    }
}

void sys_write(const char* str) {
    syscall(SYSCALL_WRITE, (void*)str, 0);
}

int sys_time() {
    int t;
    syscall(SYSCALL_TIME, &t, 0);
    return t;
}

void sys_clear() {
    syscall(SYSCALL_CLEAR, 0, 0);
}

void sys_cursor(int x, int y) {
    syscall(SYSCALL_CURSOR, (void*)(uintptr_t)x, (void*)(uintptr_t)y);
}

void sys_draw_logo(int version) {
    syscall(SYSCALL_DRAW_LOGO, (void*)(int)version, 0);
}

char sys_getchar() {
    char c;
    syscall(SYSCALL_GETCHAR, &c, 0);
    return c;
}

void sys_putchar(char c) {
    syscall(SYSCALL_PUTCHAR, (void*)(uintptr_t)c, 0);
}
void sys_sleep(int ticks) {
    syscall(SYSCALL_SLEEP, (void*)(uintptr_t)ticks, 0);
}
