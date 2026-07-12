#include <kernel/tty/tty.h>
#include <stdio.h>
#include <arch/i386/gdt/gdt.h>
#include <arch/i386/idt/idt.h>

void kernelMain() {
    terminalInit();
    printf("Successfully initialized terminal\n");

    initGdt();
    printf("Successfully initialized gdt\n");

    initIdt();
    printf("Successfully initialized idt\n");

    printf("Hello, World!\n");

    for (;;) {}
}
