//
// Created by dylan on 19/07/2026.
//

#ifndef BLU_OS_HEAP_H
#define BLU_OS_HEAP_H

#include <kernel/mm/slab.h>
#include <stddef.h>
#include <stdint.h>

// TODO add arch agnostic macros
#define KERNEL_HEAP_START 0xC1000000
#define KERNEL_HEAP_END 0xC2000000

typedef enum : uint32_t { SLAB, PAGE } KmallocAllocationType;

typedef enum : uint32_t { HEAP_ALLOCATED = 1 << 0, HEAP_FREED = 1 << 1 } KmallocFlags;

typedef struct {
    size_t size;
    uint32_t type;
    uint32_t flags;
} KmallocHeader;

extern KernelMemoryCache cache8;
extern KernelMemoryCache cache16;
extern KernelMemoryCache cache32;
extern KernelMemoryCache cache64;
extern KernelMemoryCache cache128;
extern KernelMemoryCache cache256;
extern KernelMemoryCache cache512;
extern KernelMemoryCache cache1024;
extern KernelMemoryCache cache2048;
extern KernelMemoryCache cache4096;

void* slabAlloc(size_t size);

void slabFree(void* ptr);

void heapInit();

void* allocPages(size_t numPages);

void freePages(void* ptr, size_t pages);

#endif // BLU_OS_HEAP_H
