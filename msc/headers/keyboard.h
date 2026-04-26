#pragma once
extern char* letter_buffer;

void kbd_init(void);
void kbd_handle_irq(u64 error_code);
char kbd_getchar(void);
