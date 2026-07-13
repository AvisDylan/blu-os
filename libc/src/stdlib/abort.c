//
// Created by dylan on 08/07/2026.
//

#include <stdio.h>

__attribute__((__noreturn__))
void abort() {
#ifdef __is_libk
    printf("kernel panic\n");
    asm volatile("hlt");
#else
    printf("abort\n");
#endif

    for (;;){}

    __builtin_unreachable();
}