//
// Created by dylan on 19/07/2026.
//

#include <kernel/mm/slab.h>
#include <stddef.h>
#include <kernel/mm/heap.h>

static Slab* slabCreate(uint32_t objectSize) {
    void* page = allocPages(1);

    if (!page)
        return NULL;

    Slab* slab = (Slab*) allocPages(1);

    slab->next = NULL;
    slab->memory = page;
    slab->objectSize = objectSize;
    slab->capacity = PAGE_SIZE / objectSize;
    slab->used = 0;
    slab->freeList = NULL;

    uint8_t* p = (uint8_t*) page;

    for (uint32_t i = 0; i < slab->capacity; i++) {
        void* object = p + i * objectSize;
        *(void**) object = slab->freeList;
        slab->freeList = object;
    }

    return slab;
}

KernelMemoryCache cacheCreate(uint32_t objectSize) {
    KernelMemoryCache cache;

    cache.slabsFull = NULL;
    cache.slabsPartial = NULL;
    cache.slabsEmpty = NULL;
    cache.objectSize = objectSize;

    return cache;
}

void* cacheAlloc(KernelMemoryCache* cache) {
    Slab* slab = cache->slabsPartial;

    if (!slab) {
        if (cache->slabsEmpty) {
            slab = cache->slabsEmpty;
            cache->slabsEmpty = slab->next;
        }else
            slab = slabCreate(cache->objectSize);

        slab->next = cache->slabsPartial;
        cache->slabsPartial = slab;
    }

    void* object = slab->freeList;

    slab->freeList = *(void**) object;
    slab->used++;

    if (slab->used == slab->capacity) {
        Slab** pp = &cache->slabsPartial;

        while (*pp && *pp != slab) {
            pp = &(*pp)->next;
        }

        slab->next = cache->slabsFull;
        cache->slabsFull = slab;
    }

    return object;
}

void cacheFree(KernelMemoryCache* cache, void* object) {
    Slab* slab;

    for (slab = cache->slabsPartial; slab; slab = slab->next) {
        uint8_t* base = (uint8_t*) slab->memory;
        uint8_t* end = base + slab->capacity * slab->objectSize;

        if ((uint8_t*) object >= base && (uint8_t*)object < end)
            break;
    }

    if (!slab) {
        for (slab = cache->slabsFull; slab; slab = slab->next) {
            uint8_t* base = (uint8_t*) slab->memory;
            uint8_t* end = base + slab->capacity * slab->objectSize;

            if ((uint8_t*) object >= base && (uint8_t*) object < end)
                break;
        }
    }

    if (!slab)
        return;

    *(void**) object = slab->freeList;

    slab->freeList = object;
    slab->used--;

    if (slab->used == slab->capacity - 1) {
        Slab** pp = &cache->slabsFull;

        while (*pp && *pp != slab) {
            pp = &(*pp)->next;
        }

        if (*pp == slab)
            *pp = slab->next;

        slab->next = cache->slabsPartial;
        cache->slabsPartial = slab;
    }
}