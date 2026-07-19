//
// Created by dylan on 17/07/2026.
//

#include <kernel/libk/panic.h>
#include <stdarg.h>

__attribute__((__noreturn__))
void panic(const char* restrict format, ...) {
    //TODO implement panic & add proper libk

    asm volatile("cli; hlt");

    for (;;){}

    __builtin_unreachable();
}
