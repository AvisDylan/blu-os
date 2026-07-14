#include <kernel/tty/tty.h>
#include <stdio.h>
#include <arch/i386/gdt/gdt.h>
#include <arch/i386/idt/idt.h>
#include <arch/i386/mmu/paging.h>
#include <arch/i386/mmu/physicalmemorymanager.h>
#include <arch/i386/mmu/virtualmemorymanager.h>

void kernelMain() {
    terminalInit();
    printf("Successfully initialized terminal\n");

    initGdt();
    printf("Successfully initialized gdt\n");

    initIdt();
    printf("Successfully initialized idt\n");

    //TODO add physical memory size detection
    initPhysicalMemoryManager(256);
    printf("Successfully initialized physical memory manager\n");

    initVirtualMemoryManager();
    printf("Successfully initialized virtual memory manager\n");

    // initPaging();
    // printf("Successfully initialized paging\n");

    printf("Hello, World!\n");

    for (;;) {}
}
