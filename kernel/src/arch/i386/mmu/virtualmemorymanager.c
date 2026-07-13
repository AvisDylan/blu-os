//
// Created by dylan on 14/07/2026.
//

#include <arch/i386/mmu/physicalmemorymanager.h>
#include <arch/i386/mmu/virtualmemorymanager.h>

void initVirtualMemoryManager() {
    for (int32_t i = 0; i < 1024; i++) {
        pageDirectory[i] = 0;
    }
}

void mapPage(uint32_t virtualAddress, uint32_t physicalAddress, uint32_t flags) {
    uint32_t pdIndex = virtualAddress >> 22;
    uint32_t ptIndex = (virtualAddress >> 12) & 0x3ff;

    uint32_t* pageTable = NULL;

    if ((pageDirectory[pdIndex] & PAGE_PRESENT) == 0) {
        physical_addr_t newTablePhysical = kallocFrame();

        uint32_t* tempPtr = (uint32_t*) newTablePhysical;

        for (uint32_t i = 0; i < 1024; i++) {
            tempPtr[i] = 0;
        }

        pageDirectory[pdIndex] = newTablePhysical | PAGE_PRESENT | PAGE_WRITE | flags;
    }

    pageTable = (uint32_t*) (pageDirectory[pdIndex] & ~0xFFF);
    pageTable[ptIndex] = (physicalAddress & ~0xFFF) | PAGE_PRESENT | flags;

    asm volatile("invlpg (%0)" :: "r"(virtualAddress) : "memory");
}