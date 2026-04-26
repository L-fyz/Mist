#include "mist.h"

#define pic_master_cmd 0x20
#define pic_master_data 0x21
#define pic_slave_cmd 0xA0
#define pic_slave_data 0xA1

void pic_remap(u8 offset_master, u8 offset_slave) {
    u8 a1 = inb(pic_master_data);
    u8 a2 = inb(pic_slave_data);

    outb(pic_master_cmd, 0x11);
    outb(pic_slave_cmd, 0x11);
    outb(pic_master_data, offset_master);
    outb(pic_slave_data, offset_slave);
    outb(pic_master_data, 0x04);
    outb(pic_slave_data, 0x02);
    outb(pic_master_data, 0x01);
    outb(pic_slave_data, 0x01);

    outb(pic_master_data, a1); outb(pic_slave_data, a2);
}

void pic_send_eoi(u8 irq) {
    if (irq >= 0x28) {
        outb(pic_slave_cmd, 0x20);
    }
    outb(pic_master_cmd, 0x20);
}
