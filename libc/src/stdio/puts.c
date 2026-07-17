//
// Created by dylan on 08/07/2026.
//

#include "stdio.h"

/**
 * @brief Write a string followed by newline to console.
 *
 * Writes a string to console followed by a newline character.
 *
 * @param string String to print to console.
 * @return The return value is the number of characters written or -1 in the case of failure.
 */
int puts(const char* string) {
    return printf("%s\n", string);
}
