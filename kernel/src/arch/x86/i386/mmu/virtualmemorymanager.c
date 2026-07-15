//
// Created by dylan on 14/07/2026.
//

#include <arch/x86/i386/mmu/physicalmemorymanager.h>
#include <arch/x86/i386/mmu/virtualmemorymanager.h>
#include <arch/x86/i386/mmu/paging.h>

#include "stdio.h"

uint32_t pageDirectory[1024] __attribute__((aligned(4096)));
uint32_t kernelPageTable[1024] __attribute__((aligned(4096)));

void initVirtualMemoryManager() {
    for (int32_t i = 0; i < 1024; i++) {
        pageDirectory[i] = 0;
        kernelPageTable[i] = 0;
    }

    for (uint32_t i = 0; i < 1024; i++) {
        kernelPageTable[i] = (i * 0x1000) | PAGE_PRESENT | PAGE_WRITE;
    }

    uint32_t pdIndex = KERNEL_VMA >> 22;
    uint32_t kernelPageTablePhysical = (uint32_t) kernelPageTable - KERNEL_VMA;
    pageDirectory[pdIndex] = kernelPageTablePhysical | PAGE_PRESENT | PAGE_WRITE;

    uint32_t pageDirPhysical = (uint32_t) pageDirectory - KERNEL_VMA;
    pageDirectory[1023] = pageDirPhysical | PAGE_PRESENT | PAGE_WRITE;

    loadPageDirectory((uint32_t*) pageDirPhysical);
    enablePaging();

    mapPage(0x000B8000, 0x000B8000, PAGE_WRITE);
}

void mapPage(uint32_t virtualAddress, uint32_t physicalAddress, uint32_t flags) {
    uint32_t pdIndex = virtualAddress >> 22;
    uint32_t ptIndex = (virtualAddress >> 12) & 0x3ff;

    uint32_t* virtPageDir = (uint32_t*) 0xFFFFF000;

    if ((virtPageDir[pdIndex] & PAGE_PRESENT) == 0) {
        physical_addr_t newTablePhysical = kallocFrame();

        virtPageDir[pdIndex] = newTablePhysical | PAGE_PRESENT | PAGE_WRITE | flags;

        uint32_t ptVirtualAddress = 0xFFC00000 + (pdIndex * 0x1000);

        asm volatile("invlpg (%0)" :: "r"(ptVirtualAddress) : "memory");

        uint32_t* newPageTable = (uint32_t*) ptVirtualAddress;

        for (uint32_t i = 0; i < 1024; i++) {
            newPageTable[i] = 0;
        }
    }

    uint32_t* pageTable = (uint32_t*) (0xFFC00000 + (pdIndex * 0x1000));

    pageTable[ptIndex] = (physicalAddress & ~0xFFF) | PAGE_PRESENT | flags;

    asm volatile("invlpg (%0)" :: "r"(virtualAddress) : "memory");
}