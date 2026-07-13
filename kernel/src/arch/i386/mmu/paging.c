//
// Created by dylan on 13/07/2026.
//

#include <arch/i386/mmu/paging.h>

uint32_t pageDirectory[1024] __attribute__((aligned(4096)));
uint32_t firstPageTable[1024] __attribute__((aligned(4096)));

void initPaging() {
    for (int32_t i = 0; i < 1024; i++) {
        pageDirectory[i] = 0x00000002;
    }

    for (uint32_t i = 0; i < 1024; i++) {
        firstPageTable[i] = (i * 0x1000) | (PAGE_PRESENT | PAGE_WRITE);
    }

    pageDirectory[0] = ((uint32_t) firstPageTable) | (PAGE_PRESENT | PAGE_WRITE);

    loadPageDirectory(pageDirectory);
    enablePaging();
}