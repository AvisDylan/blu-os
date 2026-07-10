//
// Created by dylan on 10/07/2026.
//

#include <arch/i386/idt/idt.h>

__attribute__((aligned(0x10)))
static IDTEntry idt[IDT_MAX_DESCRIPTORS];
static IDTR idtr;
static bool vectors[IDT_MAX_DESCRIPTORS];

void exceptionHandler() {
    asm volatile("cli; hlt");
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

    for (uint8_t vector = 0; vector < 32; vector++) {
        idtSetDescriptor(vector, isrStubTable[vector], 0x8e);
        vectors[vector] = true;
    }

    asm volatile("lidt %0" : : "m" (idtr));
    asm volatile("sti");
}