//
// Created by dylan on 19/07/2026.
//

#include <arch/x86/i386/mmu/physicalmemorymanager.h>
#include <kernel/libk/stdlib.h>
#include <kernel/mm/heap.h>
#include "kernel/libk/panic.h"

/**
 * @brief Free kernel heap memory allocations
 *
 * @note If allocation <= PAGE_SIZE it uses slab allocation else it uses page allocation.
 *
 * @param ptr Pointer to memory to free
 */
void kfree(void* ptr) {
    if (!ptr)
        return;

    KmallocHeader* kmallocHeader = ((KmallocHeader*) ptr) - 1;
    size_t size = kmallocHeader->size;

    if (kmallocHeader->flags & HEAP_FREED || !(kmallocHeader->flags & HEAP_ALLOCATED))
        panic("Tried to double free or free non-allocated memory");

    switch (kmallocHeader->type) {
        case SLAB:
            slabFree(kmallocHeader);
            break;
        case PAGE:
            break;
    }
}
