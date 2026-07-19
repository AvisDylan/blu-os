#include <kernel/tty/tty.h>
#include <arch/kal.h>
#include <kernel/libk/stdio.h>

//TODO replace libc printf with libk printf
void kernelMain() {
    terminalInit();
    kprintf("Successfully initialized terminal\n");

    kalInitGdt();
    kprintf("Successfully initialized gdt\n");

    kalInitIdt();
    kprintf("Successfully initialized idt\n");

    //TODO add physical memory size detection
    kalInitPhysicalMemoryManager(256);
    kprintf("Successfully initialized physical memory manager\n");

    kalInitVirtualMemoryManager();
    kprintf("Successfully initialized virtual memory manager\n");

    kprintf("Hello, World!\n");

    for (;;) {}
}
