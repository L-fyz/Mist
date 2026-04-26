#include "mist.h"

extern void isr32(void); 
extern void isr33(void); 
extern void isr34(void);
extern void isr35(void); 
extern void isr36(void); 
extern void isr37(void);
extern void isr38(void); 
extern void isr39(void); 
extern void isr40(void);
extern void isr41(void); 
extern void isr42(void); 
extern void isr43(void);
extern void isr44(void); 
extern void isr45(void); 
extern void isr46(void);
extern void isr47(void);

static const char letters[128] = {
    0, 0x1B, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const char letters_up[128] = {
    0, 0x1B, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0, 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

volatile char kbd_char = 0;
volatile bool kbd_ready = false;
volatile bool shift_pressed = false;

void kbd_init(void) {
    pic_remap(0x20, 0x28);

    void* irq_stubs[16] = {
        isr32, isr33, isr34, isr35, isr36, isr37, isr38, isr39,
        isr40, isr41, isr42, isr43, isr44, isr45, isr46, isr47
    };
    for (int i = 0; i < 16; i++) {
        idt_set_gate(0x20 + i, irq_stubs[i], 0x0E, 0);
    }
    outb(0x21, inb(0x21) & 0xFD);
    kbd_ready = false;
    kbd_char = 0;
    shift_pressed = false;
}

void kbd_handle_irq(u64 error_code) {
    (void)error_code;
    u8 sc = inb(0x60);

    if ((sc >= 128) && !(sc == 0xAA || sc == 0xB6)) {
        return;
    }

    if ((sc == 0x2A) || (sc == 0x36)) {
        shift_pressed = true;
        return;
    }

    if ((sc == 0xAA) || (sc == 0xB6)) {
        shift_pressed = false;
        return;
    }

    if (!shift_pressed) {
        kbd_char = letters[sc];
        kbd_ready = true;
        return;
    } else {
        kbd_char = letters_up[sc];
        kbd_ready = true;
        return;
    }
}

char kbd_getchar(void) {
    while (!kbd_ready) __asm__ volatile("sti; hlt");
    char c = kbd_char;
    kbd_ready = false;
    return c;
}
