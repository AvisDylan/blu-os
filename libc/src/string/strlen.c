//
// Created by dylan on 08/07/2026.
//

#include <stddef.h>
#include <string.h>

size_t strlen(const char* str) {
    size_t length = 0;

    while (str[length]) {
        length++;
    }

    return length;
}