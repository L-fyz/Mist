#include "mist.h"

u16 cursor_x = 0;
u16 cursor_y = 0;

void cursor_sync(void) {
    u16 pos = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14); outb(0x3D5, pos >> 8);
    outb(0x3D4, 15); outb(0x3D5, pos & 0xFF);
}

void cursor_upd(int x, int y) {
    cursor_x = x;
    cursor_y = y;
    cursor_sync();
}

void clear(void) {
    vga_clear();
    cursor_upd(0, 0);
}

void putchar(char c) {
    if (c == '\n') {
        cursor_upd(0, ++cursor_y);
    } else {
        vga_putchar(cursor_x, cursor_y, c);
        cursor_upd(++cursor_x, cursor_y);
        if (cursor_x >= 80) {
            cursor_upd(0, ++cursor_y);
        }
    }
    if (cursor_y >= 25) {
        vga_scrollup();
        cursor_upd(cursor_x, 24);
    }
}

void delchar(void) {
    if ((cursor_x == 0) && (cursor_y == 0)) {
        return;
    } else if (cursor_x == 0) {
        vga_putchar(79, --cursor_y, 0);
        cursor_upd(79, cursor_y);
        cursor_sync();
    } else {
        vga_putchar(--cursor_x, cursor_y, 0);
        cursor_sync();
    }
}

void print_str(const char* c) {
    while (*c) {
        putchar(*c);
        c++;
    }
}

void print_num(u64 i, int base) {
    char* string = u2s(i, str, base);
    print_str(string);
}
