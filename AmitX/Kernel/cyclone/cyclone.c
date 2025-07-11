#include "cyclone.h"
#include "kernel.h"
#include "screen.h"
#include "keyboard.h"
#include "time.h"
#include "logo.h"
#include "commands.h"
#include "string.h"

extern int menu;
int version = 1;

void cyclone_main(int first) {
    menu = 0;
    screen_clear();
    screen_puts("Cyclone REPL v0.1\nType 'help' for commands\n\n");
    draw_logo(version);

    char input[128];
    int pos = 0;

    while (1) {
        screen_puts("> ");
        pos = 0;

        while (1) {
            char c = keyboard_getchar();

            if (first) {
                screen_putc('\b');
                screen_putc('\b');
                break;
            }

            if (c == '\n') {
                input[pos] = '\0';
                screen_newline();
                execute_command(input);
                break;
            } else if (c == '\b') {
                if (pos > 0) {
                    pos--;
                    screen_putc('\b');
                    screen_putc(' ');
                    screen_putc('\b');
                }
            } else if (c >= 32 && pos < sizeof(input) - 1) {
                input[pos++] = c;
                screen_putc(c);
            }
        }
        first = 0;

        // Echo back input for now (testing)
    }
}
