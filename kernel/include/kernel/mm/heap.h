//
// Created by dylan on 19/07/2026.
//

#ifndef BLU_OS_HEAP_H
#define BLU_OS_HEAP_H

#include <stddef.h>

//TODO add arch agnostic macros
#define KERNEL_HEAP_START 0xC1000000
#define KERNEL_HEAP_END 0xC2000000
#define PAGE_SIZE 0x1000

void* allocPages(size_t numPages);

#endif //BLU_OS_HEAP_H
