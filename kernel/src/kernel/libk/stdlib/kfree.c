//
// Created by dylan on 19/07/2026.
//

#include <kernel/libk/stdlib.h>
#include <arch/x86/i386/mmu/physicalmemorymanager.h>
#include <kernel/mm/heap.h>

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

    if (size <= PAGE_SIZE) {
        slabFree(kmallocHeader);
        return;
    }

    //TODO add page freeing
}
