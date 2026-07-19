#include <kernel/tty/tty.h>
#include <arch/kal.h>
#include <kernel/libk/stdio.h>
#include <kernel/mm/heap.h>
#include <kernel/libk/stdlib.h>

/*typedef struct {
    uint32_t x;
} Example;*/

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

    heapInit();
    kprintf("Successfully initialized heap\n");

    /*Example* example = kmalloc(sizeof(Example));

    kprintf("%x", example);

    kfree(example);*/

    kprintf("Hello, World!\n");

    for (;;) {}
}
