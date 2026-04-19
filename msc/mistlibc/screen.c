#include "types.h"
#include "VGA.h"
#define vga ((volatile u16*)0xB8000)

static u16 cursor_x = 0;
static u16 cursor_y = 0;

void clear(void) {
    vga_clear();
    cursor_x = 0;
    cursor_y = 0;
}

void putchar(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        vga_putchar(cursor_x, cursor_y, c);
        cursor_x++;
        if (cursor_x >= 80) {
            cursor_x = 0;
            cursor_y++;
        }
    }
    if (cursor_y >= 25) {
        vga_scrollup();
        cursor_y = 24;
    }
}

void print(const char* c) {
    while (*c) {
        putchar(*c);
        c++;
    }
}
