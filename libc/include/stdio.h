//
// Created by dylan on 08/07/2026.
//

#ifndef BLU_OS_STDIO_H
#define BLU_OS_STDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file stdio.h
 * @brief Standard I/0
 */

#include <sys/cdefs.h>
#include <stdarg.h>

#define EOF (-1)

int printf(const char* __restrict, ...);
int vprintf(const char* __restrict, va_list);
int putchar(int);
int puts(const char*);

#ifdef __cplusplus
}
#endif

#endif //BLU_OS_STDIO_H
