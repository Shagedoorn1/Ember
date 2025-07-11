#include "commands.h"
#include "cyclone.h"
#include "screen.h"
#include "string.h"
#include "utils.h"
#include "kernel.h"
#include "fs.h"
#include "time.h"

extern int tick_count;
extern int load_cyclone;
extern int version;


void execute_command(const char* input) {
    screen_puts(">> ");
    if (starts_with(input, "echo ") || starts_with(input, "hoot ")) {
        const char* message = input + 5;  // Skip "echo "
        screen_puts(message);
    } else if (starts_with(input, "hex ")) {
        const char* num = input + 4;
        uint32_t number = atoi(num);
        screen_puthex(number);
    } else if (starts_with(input, "read ")) {
        const char* file = input + 5;
        screen_puts(file);
        screen_newline();


        char path[64];
        strcpy(path, "/Saved/");  // Copy folder path into buffer
        strcat(path, file);       // Safely append the filename
        
        screen_puts(path);
        screen_newline();

        const char* content = fs_read(path);
        screen_puts(content);
    } else if (strcmp(input, "coffee") == 0) {
        uint32_t number = 12648430;
        screen_puthex(number);
    } else if (strcmp(input, "time") == 0) {
        int time = tick_count / 100;
        screen_puts("Uptime: ");
        screen_putint(time);
        screen_puts(" seconds");
    } else if (strcmp(input, "back") == 0) {
        load_cyclone = 0;
        cyclone_main(0);
        draw_start();
    } else if (strcmp(input, "switch logo") == 0) {
        if (version == 1) {
            version++;
        } else if (version == 2) {
            version--;
        }
        cyclone_main(0);
    } else if (strcmp(input, "help") == 0) {
        screen_puts("Available commands:\n");
        screen_puts("  echo/hoot <text>   - Print text\n");
        screen_puts("  hex <number>       - Print number as hex\n");
        screen_puts("  time               - Show uptime\n");
        screen_puts("  clear              - Clear screen\n");
        screen_puts("  back               - Return to menu\n");
        screen_puts("  quit               - Exit system\n");
        screen_puts("  coffee             - Print 0xC0FFEE\n");
        screen_puts("  ls                 - Print files\n");
        screen_puts("  switch logo        - Switch Owly ASCII art");
    } else if (strcmp(input, "ls") == 0) {
        screen_puts("\b\b\b");
        fs_debug_list();
    } else if (strcmp(input, "quit") == 0) {
        sleep(1);
        qemu_exit(0);
    } else if (strcmp(input, "clear") == 0) {
        cyclone_main(0);
    } else {
        screen_puts("Unknown command");
    }
    screen_newline();
}