//
// Created by dylan on 17/07/2026.
//

#ifndef BLU_OS_PANIC_H
#define BLU_OS_PANIC_H

__attribute__((__noreturn__))
void panic(const char* __restrict, ...);

#endif //BLU_OS_PANIC_H
