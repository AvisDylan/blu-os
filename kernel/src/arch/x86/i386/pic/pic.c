//
// Created by dylan on 11/07/2026.
//

#include <arch/x86/i386/pic/pic.h>
#include <arch/x86/i386/io/io.h>

void picSendEoi(uint8_t irq) {
    if (irq >= 8)
        outb(PIC2_COMMAND,PIC_EOI);

    outb(PIC1_COMMAND, PIC_EOI);
}

void remapPic(uint32_t offset1, uint32_t offset2) {
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    ioWait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    ioWait();
    outb(PIC1_DATA, offset1);
    ioWait();
    outb(PIC2_DATA, offset2);
    ioWait();
    outb(PIC1_DATA, 1 << CASCADE_IRQ);
    ioWait();
    outb(PIC2_DATA, CASCADE_IRQ);
    ioWait();

    outb(PIC1_DATA, ICW4_8086);
    ioWait();
    outb(PIC2_DATA, ICW4_8086);
    ioWait();

    outb(PIC1_DATA, 0);
    outb(PIC2_DATA, 0);
}

void disablePic() {
    outb(PIC1_DATA, 0xff);
    outb(PIC2_DATA, 0xff);
}

void irqSetMask(uint8_t irqLine) {
    uint16_t port;
    uint8_t value;

    if (irqLine < 8)
        port = PIC1_DATA;
    else {
        port = PIC2_DATA;
        irqLine -= 8;
    }

    value = inb(port) | (1 << irqLine);
    outb(port, value);
}

void irqClearMask(uint8_t irqLine) {
    uint16_t port;
    uint8_t value;

    if (irqLine < 8)
        port = PIC1_DATA;
    else {
        port = PIC2_DATA;
        irqLine -= 8;
    }

    value = inb(port) & ~(1 << irqLine);
    outb(port, value);
}

static uint16_t getPicIrqReg(uint32_t ocw3) {
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);

    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}


uint16_t getPicIrr() {
    return getPicIrqReg(PIC_READ_IRR);
}

uint16_t getPicIsr() {
    return getPicIrqReg(PIC_READ_ISR);
}