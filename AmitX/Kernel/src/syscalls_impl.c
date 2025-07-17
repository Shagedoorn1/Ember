#include "syscall.h"
#include "screen.h"
#include "time.h"
#include "keyboard.h"
#include "logo.h"

int sys_write(uint32_t str_ptr, uint32_t _, uint32_t __) {
    const char* str = (const char*)str_ptr;
    puts(str);
    return 0;
}

int sys_clear(uint32_t _, uint32_t __, uint32_t ___) {
    clear();
    return 0;
}

// Register them in kernel setup
void register_all_syscalls() {
    register_syscall(SYSCALL_WRITE, sys_write);
    register_syscall(SYSCALL_CLEAR, sys_clear);
    // ...and so on
}