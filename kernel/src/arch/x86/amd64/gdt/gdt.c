//
// Created by dylan on 08/07/2026.
//

#include <arch/x86/amd64/gdt/gdt.h>
#include <stdint.h>
#include <stdio.h>
#include <kernel/libk/stdio.h>

static uint8_t gdt[3][8];

void encodeGdtEntry(uint8_t* target, GDT source) {
    if (source.limit > 0xfffff) {
        kprintf("GDT cannot encode limits larger than 0xffffF\n");
        return;
    }
    
    target[0] = source.limit & 0xff;
    target[1] = (source.limit >> 8) & 0xff;
    target[6] = (source.limit >> 16) & 0x0f;
    
    target[2] = source.base & 0xff;
    target[3] = (source.base >> 8) & 0xff;
    target[4] = (source.base >> 16) & 0xff;
    target[7] = (source.base >> 24) & 0xff;
    
    target[5] = source.accessBytes;
    
    target[6] |= (source.flags << 4);
}

void initGdt() {
    GDT entry;

    //null entry
    entry.base = 0;
    entry.limit = 0;
    entry.accessBytes = 0;
    entry.flags = 0;

    encodeGdtEntry(gdt[0], entry);

    //kernel code
    entry.base = 0;
    entry.limit = 0xfffff;
    entry.accessBytes = 0x9a;
    entry.flags = 0xa;

    encodeGdtEntry(gdt[1], entry);

    //kernel data
    entry.base = 0;
    entry.limit = 0xfffff;
    entry.accessBytes = 0x92;
    entry.flags = 0xc;

    encodeGdtEntry(gdt[2], entry);

    uint16_t limit = (sizeof(uint8_t) * 3 * 8) - 1;
    uint64_t base = (uint64_t) &gdt;

    setGdt(limit, base);
}
