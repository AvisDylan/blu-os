#include <kernel/tty/tty.h>
#include <stdio.h>
#include <arch/kal.h>

void kernelMain() {
    terminalInit();
    printf("Successfully initialized terminal\n");

    kalInitGdt();
    printf("Successfully initialized gdt\n");

    kalInitIdt();
    printf("Successfully initialized idt\n");

    //TODO add physical memory size detection
    kalInitPhysicalMemoryManager(256);
    printf("Successfully initialized physical memory manager\n");

    kalInitVirtualMemoryManager();
    printf("Successfully initialized virtual memory manager\n");

    printf("Hello, World!\n");

    for (;;) {}
}
