//
// Created by dylan on 08/07/2026.
//

#include <stdarg.h>
#include <stdio.h>

/**
 * @brief A wrapper around vprintf().
 *
 * Initializes a @c va_list and forwards all printing and formatting to vprintf().
 *
 * @param format Format string containing both ordinary characters and format specifiers.
 * @param ... Arguments referenced by @p format.
 * @return The return value is the number of characters written or -1 in the case of failure.
 *
 * @see vprintf()
 */
int printf(const char* restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int result = vprintf(format, parameters);

    va_end(parameters);

    return result;
}
