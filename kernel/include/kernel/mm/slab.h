//
// Created by dylan on 19/07/2026.
//

#ifndef BLU_OS_SLAB_H
#define BLU_OS_SLAB_H

#include <stdint.h>

typedef struct slab {
    struct slab* next;
    void* memory;
    uint32_t objectSize;
    uint32_t capacity;
    uint32_t used;
    void* freeList;
} Slab;

typedef struct {
    Slab* slabsFull;
    Slab* slabsPartial;
    Slab* slabsEmpty;

    uint32_t objectSize;
} KernelMemoryCache;

KernelMemoryCache cacheCreate(uint32_t objectSize);
void* cacheAlloc(KernelMemoryCache* cache);
void cacheFree(KernelMemoryCache* cache, void* object);

#endif //BLU_OS_SLAB_H
