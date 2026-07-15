//
// Created by dylan on 14/07/2026.
//

#include <arch/x86/i386/mmu/physicalmemorymanager.h>
#include <stdio.h>

static uint8_t* frameMap;
static physical_addr_t startFrame;
static uint32_t totalPages;

static physical_addr_t preFrames[20];
static uint8_t pframeIndex = 20;

static physical_addr_t kallocFrameInt() {
    for (uint32_t i = 0; i < totalPages; i++) {
        if (frameMap[i] == FREE) {
            frameMap[i] = USED;

            return startFrame + (i * PAGE_SIZE);
        }
    }

    return ERROR;
}

void initPhysicalMemoryManager(size_t memSizeInMb) {
    startFrame = (physical_addr_t) (((uintptr_t) &endKernel - KERNEL_VMA + (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1));

    uint32_t maxPages = (memSizeInMb * 1024 * 1024) / PAGE_SIZE;

    if (maxPages > 1048576)
        maxPages = 1048576;

    totalPages = maxPages;

    frameMap = (uint8_t*) ((uintptr_t) startFrame + KERNEL_VMA);

    uint32_t frameMapPages = (totalPages + (PAGE_SIZE - 1)) / PAGE_SIZE;

    for (uint32_t i = 0; i < totalPages; i++) {
        if (i < frameMapPages)
            frameMap[i] = USED;
        else
            frameMap[i] = FREE;
    }
}

physical_addr_t kallocFrame() {
    if (pframeIndex >= 20) {
        for (int32_t i = 0; i < 20; i++) {
            preFrames[i] = kallocFrameInt();
        }

        pframeIndex = 0;
    }

    physical_addr_t allocatedFrame = preFrames[pframeIndex];

    pframeIndex++;

    return allocatedFrame;
}

void kfreeFrame(physical_addr_t frameAddress) {
    if (frameAddress < startFrame)
        return;

    physical_addr_t offset = frameAddress - startFrame;
    uint32_t index = offset / PAGE_SIZE;

    if (index < totalPages)
        frameMap[index] = FREE;
}