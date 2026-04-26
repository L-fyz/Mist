#pragma once

extern u16 cursor_x;
extern u16 cursor_y;

void cursor_upd(int x, int y);
void clear(void);
void putchar(char i);
void delchar(void);
void print_str(const char* c);
void print_num(u64 i, int base);
