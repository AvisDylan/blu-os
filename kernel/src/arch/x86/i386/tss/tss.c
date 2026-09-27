#include <arch/x86/i386/tss/tss.h>
#include <string.h>

Tss tss;

void tssInit(void) {
    memset(&tss, 0, sizeof(Tss));
    tss.ss0 = 0x10;
    tss.iomapBase = sizeof(Tss);
}

void loadTss(uint16_t selector) { asm volatile("ltr %0" ::"r"(selector)); }
