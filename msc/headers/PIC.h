#pragma once

static inline void outb(u16 port, u8 val);
static inline u8 inb(u16 port);
void pic_remap(u8 offset_master, u8 offset_slave);
void pic_send_eoi(u8 irq);
