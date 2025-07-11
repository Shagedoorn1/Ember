#include "screen.h"
#include "logo.h"
#include "amitx_info.h"

void draw_logo(int version) {
    
    switch (version) {
        case 1:
            draw_logo1();
            break;
        case 2:
            draw_logo2();
            break;
        default:
            draw_logo1();
            break;
    }
    
}

void draw_logo1() {
    screen_move_cursor(0, 2);
    screen_puts("     ___\n");
    screen_puts("    (o,o)\n");
    screen_puts("    {\" \"}\n");
    screen_puts("     \" \" \n");
    screen_puts("  Owly, by Amity\n");

}
void draw_logo2() {
    screen_move_cursor(0, 2);
    screen_puts("    ____________\n");
    screen_puts("   / ____  ____ \\\n");
    screen_puts("  / / @  \\/ @  \\ \\\n");
    screen_puts("  \\ \\____/\\____/ /\\\n");
    screen_puts("   \\_____\\/_____/||\n");
    screen_puts("   /       /\\\\\\\\\\//\n");
    screen_puts("   |0xC0FFEE\\\\\\\\\\\\\n");
    screen_puts("   \\        \\\\\\\\\\\\\n");
    screen_puts("    \\________/\\\\\\\\\n");
    screen_puts("      _||_||_  \\\\\\\n");
    screen_puts("       -- --    \\\\\n");
    screen_puts("    Owly, by Amity\n");
}