#include "types.h"
#define vga ((volatile u16*)0xB8000)

void vga_clear(void) {
    for (usize i = 0; i < 2000; i++) {
        vga[i] = 0;
    }
}

void vga_putchar(u16 x, u16 y, char c) {
    vga[y * 80 + x] = (u16)((u8)c | (0x07 << 8));
}

void vga_scrollup() {
    for (usize i = 0; i < 24 * 80; i++) {
        vga[i] = vga[i + 80];
    }
    for (usize i = 0; i < 80; i++) {
        vga[24 * 80 + i] = 0;
    }
}

char vga_getchar(u16 x, u16 y) {
    return (char)(vga[80*y+x] & 0xFF);
}
