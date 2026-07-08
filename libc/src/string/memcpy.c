//
// Created by dylan on 08/07/2026.
//

#include <stddef.h>
#include <string.h>

void* memcpy(void* restrict dstPtr, const void* restrict srcPtr, size_t size) {
    unsigned char* dst = (unsigned char*) dstPtr;
    const unsigned char* src = (unsigned char*) srcPtr;

    for (size_t i = 0; i < size; i++) {
        dst[i] = src[i];
    }

    return dstPtr;
}
