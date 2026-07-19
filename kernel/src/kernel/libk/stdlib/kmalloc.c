//
// Created by dylan on 19/07/2026.
//

#include <kernel/libk/stdlib.h>
#include <kernel/mm/slab.h>
#include <kernel/mm/heap.h>
#include <arch/x86/i386/mmu/physicalmemorymanager.h>

/**
 * @brief Kernel heap memory allocator.
 *
 * @note If allocation <= PAGE_SIZE it uses slab allocation else it uses page allocation.
 *
 * @param size Size of memory allocation.
 * @return Pointer to allocated memory.
 */
void* kmalloc(size_t size) {
    size_t total = size + sizeof(KmallocHeader);

    if (total <= PAGE_SIZE) {
        void* memory = slabAlloc(total);

        if (!memory)
            return NULL;

        KmallocHeader* kmallocHeader = (KmallocHeader*) memory;

        kmallocHeader->size = total;

        return (void*) (kmallocHeader + 1);
    }

    size_t pages = (total + PAGE_SIZE - 1) / PAGE_SIZE;

    void* memory = allocPages(pages);

    if (!memory)
        return NULL;

    KmallocHeader* kmallocHeader = (KmallocHeader*) memory;

    kmallocHeader->size = pages * PAGE_SIZE;

    return (void*) (kmallocHeader + 1);
}

