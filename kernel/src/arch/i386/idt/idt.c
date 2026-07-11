//
// Created by dylan on 10/07/2026.
//

#include <arch/i386/idt/idt.h>
#include <arch/i386/pic/pic.h>

#include "stdio.h"

__attribute__((aligned(0x10)))
static IDTEntry idt[IDT_MAX_DESCRIPTORS];
static IDTR idtr;
static uint64_t ticks = 0;

void exceptionHandler() {
    asm volatile("cli; hlt");
}

void irqHandler(uint32_t vector, uint32_t errorCode) {
    uint8_t irq = vector - 32;

    switch (irq) {
        case 0:
            //timer
            ticks++;

            if (ticks % 100 == 0)
                printf("tick\n");

            break;
        case 1:
            //keybaord
            break;
    }

    picSendEoi(irq);
}

void idtSetDescriptor(uint8_t vector, void* isr, uint8_t flags) {
    IDTEntry* descriptor = &idt[vector];

    descriptor->isrLow = (uint32_t) isr & 0xffff;
    descriptor->kernelCs = 0x08;
    descriptor->attributes = flags;
    descriptor->isrHigh = (uint32_t) isr >> 16;
    descriptor->reserved = 0;
}

void initIdt() {
    idtr.base = (uintptr_t) &idt[0];
    idtr.limit = (uint16_t) sizeof(IDTEntry) * IDT_MAX_DESCRIPTORS - 1;

    //exceptions
    for (uint8_t v = 0; v < 32; v++){
        idtSetDescriptor(v, isrStubTable[v], 0x8e);
    }

    //irqs
    for (uint8_t irq = 0; irq < 16; irq++) {
        idtSetDescriptor(32 + irq, irqStubTable[irq], 0x8e);
    }

    remapPic(0x20, 0x28);

    asm volatile("lidt %0" : : "m" (idtr));
    asm volatile("sti");
}