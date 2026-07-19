//
// Created by dylan on 19/07/2026.
//

#ifndef BLU_OS_HEAP_H
#define BLU_OS_HEAP_H

#include <stddef.h>
#include <kernel/mm/slab.h>

//TODO add arch agnostic macros
#define KERNEL_HEAP_START 0xC1000000
#define KERNEL_HEAP_END 0xC2000000

typedef struct {
    size_t size;
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

#endif //BLU_OS_HEAP_H
