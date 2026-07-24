#include <kernel/tty/tty.h>
#include <arch/kal.h>
#include <kernel/libk/stdio.h>
#include <kernel/mm/heap.h>
#include <kernel/libk/stdlib.h>

int thread1() {
    kprintf("Thread 1");

    return 0;
}

int thread2() {
    kprintf("Thread 2");

    return 0;
}

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

    thread_t* t1 = createThread(thread1, 4096);
    thread_t* t2 = createThread(thread2, 4096);

    threadSwitch(NULL, t1);
    threadSwitch(NULL, t2);

    kprintf("Hello, World!\n");

    for (;;) {}
}
