//
// Created by dylan on 19/07/2026.
//

#ifndef BLU_OS_STRING_H
#define BLU_OS_STRING_H

#include <stddef.h>

size_t strlen(const char* str);

void* memset(void* dst, int value, size_t count);

void* memmove(void* dst, const void* src, size_t count);

#endif // BLU_OS_STRING_H
