//
// Created by dylan on 17/07/2026.
//

#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

static bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*) data;

    for (size_t i = 0; i < length; i++) {
        if (putchar(bytes[i]) == EOF)
            return false;
    }

    return true;
}

/**
 * @brief A formatted print function using a @c va_list.
 *
 * Parses the format string and writes formatted output to the console.
 *
 * @param format Format string containing both ordinary characters and format specifiers.
 * @param parameters A va_list of arguments.
 * @return The return value is the number of characters written or -1 in the case of failure.
 */
int vprintf(const char* restrict format, va_list parameters) {
    int written = 0;

    while (*format != '\0') {
        size_t maxRem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;

            size_t amount = 1;

            while (format[amount] && format[amount] != '%') {
                amount++;
            }

            if (maxRem < amount) {

                return -1;
            }

            if (!print(format, amount))
                return -1;

            format += amount;
            written += amount;

            continue;
        }

        const char* formatBegunAt = format++;

        switch (*format) {
            case 'c': {
                format++;
                char c = (char) va_arg(parameters, int);

                if (!maxRem) {

                    return -1;
                }

                if (!print(&c, sizeof(c)))
                    return -1;

                written++;

                break;
            }
            case 's': {
                format++;
                const char* str = va_arg(parameters, const char*);
                size_t length = strlen(str);

                if (maxRem < length) {

                    return -1;
                }

                if (!print(str, length))
                    return -1;

                written += length;
                break;
            }
            case 'x': {
                format++;

                uint32_t value = va_arg(parameters, uint32_t);

                char buffer[16];
                size_t length = 0;

                if (value == 0)
                    buffer[length++] = '0';
                else {
                    while (value != 0) {
                        uint32_t digit = value & 0xF;
                        buffer[length++] = digit < 10 ? ('0' + digit) : ('a' + (digit - 10));
                        value >>= 4;
                    }
                }

                for (size_t i = 0; i < length / 2; i++) {
                    char tmp = buffer[i];
                    buffer[i] = buffer[length - 1 - i];
                    buffer[length - 1 - i] = tmp;
                }

                if (maxRem < length) {

                    return -1;
                }

                if (!print(buffer, length))
                    return -1;

                written += length;
                break;
            }
            default: {
                format = formatBegunAt;
                size_t length = strlen(format);

                if (maxRem < length) {

                    return -1;
                }

                if (!print(format, length))
                    return -1;

                written += length;
                format += length;
                break;
            }
        }
    }
}
