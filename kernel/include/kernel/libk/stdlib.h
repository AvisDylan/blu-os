//
// Created by dylan on 19/07/2026.
//

#ifndef BLU_OS_STDLIB_H
#define BLU_OS_STDLIB_H

#include <stddef.h>

void* kmalloc(size_t size);

void kfree(void* ptr);

#endif //BLU_OS_STDLIB_H
