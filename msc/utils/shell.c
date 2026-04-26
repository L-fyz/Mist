#include "mist.h"

u16 shell_y = 0;
u16 shell_x = 0;

void shell_init(void) {
    print_str("\n> ");
    while (1) {
        char c = kbd_getchar();
        if (c == '\b') {
            if (((shell_y == 0) && (cursor_x >= 3)) || (shell_y > 0)) {
                delchar();
            }
        } else if (c == '\n') {
            shell_y = 0;
            print_str("\n> ");
        } else if (c >= 0x20 && c <= 0x7E) {
            putchar(c);
            if (cursor_x == 0) {
                shell_y++;
            }
        }
    }
}
