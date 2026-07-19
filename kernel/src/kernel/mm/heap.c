//
// Created by dylan on 19/07/2026.
//

#include <kernel/mm/heap.h>
#include <stdint.h>
#include <arch/x86/i386/mmu/physicalmemorymanager.h>
#include <arch/x86/i386/mmu/virtualmemorymanager.h>
#include <kernel/mm/slab.h>

static uint32_t heapNext = KERNEL_HEAP_START;

KernelMemoryCache cache8;
KernelMemoryCache cache16;
KernelMemoryCache cache32;
KernelMemoryCache cache64;
KernelMemoryCache cache128;
KernelMemoryCache cache256;
KernelMemoryCache cache512;
KernelMemoryCache cache1024;
KernelMemoryCache cache2048;
KernelMemoryCache cache4096;

void heapInit() {
    cache8 = cacheCreate(8);
    cache16 = cacheCreate(16);
    cache32 = cacheCreate(32);
    cache64 = cacheCreate(64);
    cache128 = cacheCreate(128);
    cache256 = cacheCreate(256);
    cache512 = cacheCreate(512);
    cache1024 = cacheCreate(1024);
    cache2048 = cacheCreate(2048);
    cache4096 = cacheCreate(4096);
}

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

void* slabAlloc(size_t size) {
    if (size <= 8)
        return cacheAlloc(&cache8);

    if (size <= 16)
        return cacheAlloc(&cache16);

    if (size <= 32)
        return cacheAlloc(&cache32);

    if (size <= 64)
        return cacheAlloc(&cache64);

    if (size <= 128)
        return cacheAlloc(&cache128);

    if (size <= 256)
        return cacheAlloc(&cache256);

    if (size <= 512)
        return cacheAlloc(&cache512);

    if (size <= 1024)
        return cacheAlloc(&cache1024);

    if (size <= 2048)
        return cacheAlloc(&cache2048);

    if (size <= 4096)
        return cacheAlloc(&cache4096);

    return NULL;
}

void slabFree(void* ptr) {
    cacheFree(&cache8, ptr);
    cacheFree(&cache16, ptr);
    cacheFree(&cache32, ptr);
    cacheFree(&cache64, ptr);
    cacheFree(&cache128, ptr);
    cacheFree(&cache256, ptr);
    cacheFree(&cache512, ptr);
    cacheFree(&cache1024, ptr);
    cacheFree(&cache2048, ptr);
    cacheFree(&cache4096, ptr);
}

