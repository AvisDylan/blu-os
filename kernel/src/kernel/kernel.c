#include <kernel/tty/tty.h>
#include <stdio.h>
#include <arch/i386/gdt/gdt.h>

void kernelMain() {
    terminalInit();
    printf("Successfully initialized terminal\n");

    initGdt();
    printf("Successfully initialized gdt\n");

    printf("Hello, world!");
}
