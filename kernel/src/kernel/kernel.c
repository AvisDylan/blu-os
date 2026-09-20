// Created by Avis on 24/08/2026

#include <arch/kal.h>
#include <arch/x86/boot/multiboot.h>
#include <kernel/libk/stdio.h>
#include <kernel/libk/stdlib.h>
#include <kernel/mm/heap.h>
#include <kernel/tty/tty.h>
#include <stdint.h>
#include "arch/x86/i386/mmu/physicalmemorymanager.h"
#include "kernel/scheduler/scheduler.h"
#include "kernel/thread/thread.h"

int thread1() {
    kprintf("Thread 1a\n");
    schedulerYield();
    kprintf("Thread 1b\n");

    return 0;
}

int thread2() {
    kprintf("Thread 2a\n");
    schedulerYield();
    kprintf("Thread 2b\n");

    return 0;
}

void kernelMain(uint32_t magic, uint32_t mbiAddress) {
    if (magic != MULTI_BOOT_MAGIC) {
        for (;;) {
            asm volatile("hlt");
        }
    }

    MultibootInfo* multiBootInfo = (MultibootInfo*) mbiAddress;

    terminalInit();
    kprintf("Successfully initialized terminal\n");

    kalInitGdt();
    kprintf("Successfully initialized gdt\n");

    kalInitIdt();
    kprintf("Successfully initialized idt\n");

    uint32_t highestUsableAddress = 0;

    if (multiBootInfo->flags & MULTIBOOT_INFO_MEM_MAP) {
        uint8_t* memoryMapPtr = (uint8_t*) multiBootInfo->mmapAddr;
        uint8_t* memoryMapEnd = memoryMapPtr + multiBootInfo->mmapLength;

        while (memoryMapPtr < memoryMapEnd) {
            MultibootMemoryMapEntry* entry = (MultibootMemoryMapEntry*) memoryMapPtr;

            if (entry->type == MULTIBOOT_MEMORY_AVAILABLE) {
                uint64_t regionEnd = entry->addr + entry->len;

                if (regionEnd <= 0xFFFFFFFF && (uint32_t) regionEnd > highestUsableAddress)
                    highestUsableAddress = (uint32_t) regionEnd;
            }

            memoryMapPtr += entry->size + sizeof(entry->size);
        }
    } else
        highestUsableAddress = 0x100000 + (multiBootInfo->memUpper * 1024);

    uint32_t memSizeInMb = highestUsableAddress / (1024 * 1024);

    kalInitPhysicalMemoryManager(memSizeInMb);
    kprintf("Successfully initialized physical memory manager with %u mb of memory\n");

    if (multiBootInfo->flags & MULTIBOOT_INFO_MEM_MAP) {
        uint8_t* memoryMapPtr = (uint8_t*) multiBootInfo->mmapAddr;
        uint8_t* memoryMapEnd = memoryMapPtr + multiBootInfo->mmapLength;

        while (memoryMapPtr < memoryMapEnd) {
            MultibootMemoryMapEntry* entry = (MultibootMemoryMapEntry*) memoryMapPtr;

            if (entry->type != MULTIBOOT_MEMORY_AVAILABLE)
                kalMarkRangeUsed((physical_addr_t) entry->addr, (size_t) entry->len);

            memoryMapPtr += entry->size + sizeof(entry->size);
        }
    }

    kalInitVirtualMemoryManager();
    kprintf("Successfully initialized virtual memory manager\n");

    heapInit();
    kprintf("Successfully initialized heap\n");

    schedulerInit();
    kprintf("Successfully initialized scheduler\n");

    Thread* t1 = createThread(thread1, 4096);
    Thread* t2 = createThread(thread2, 4096);

    schedulerAddThread(t1);

    schedulerAddThread(t2);

    schedulerYield();

    kprintf("Back to kernel main\n");

    kprintf("Hello, World!\n");

    for (;;) {
    }
}
