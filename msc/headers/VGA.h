#pragma once
#include "types.h"

void vga_clear(void);
void vga_putchar(u16 x, u16 y, char c);
void vga_scrollup();
char vga_getchar(u16 x, u16 y);
