//
// Created by dylan on 08/07/2026.
//

#ifndef BLU_OS_TTY_H
#define BLU_OS_TTY_H

#include <arch/x86/boot/multiboot.h>
#include <stddef.h>
#include <stdint.h>

void terminalInit(MultibootInfo* multiboot);

void terminalSetColor(uint8_t color);

void terminalPutChar(char c);

void terminalWrite(const char* data, size_t size);

#endif // BLU_OS_TTY_H
