//
// Created by dylan on 08/07/2026.
//

#ifndef BLU_OS_STDIO_H
#define BLU_OS_STDIO_H

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

#ifdef __cplusplus
}
#endif

#endif //BLU_OS_STDIO_H
