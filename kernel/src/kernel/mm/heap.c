//
// Created by dylan on 19/07/2026.
//

#include <kernel/mm/heap.h>
#include <stdint.h>
#include <arch/x86/i386/mmu/physicalmemorymanager.h>
#include <arch/x86/i386/mmu/virtualmemorymanager.h>

static uint32_t heapNext = KERNEL_HEAP_START;

void* allocPages(size_t numPages) {
    uint32_t base = heapNext;
    uint32_t size = numPages * PAGE_SIZE;

    if (heapNext + size > KERNEL_HEAP_END)
        return NULL;

    for (size_t i = 0; i < numPages; i++) {
        uint32_t virtualAddress = base + i * PAGE_SIZE;
        physical_addr_t physicalAddress = kallocFrame();
        mapPage(virtualAddress, physicalAddress, PAGE_WRITE);
    }

    heapNext += size;

    return (void*) base;
}

