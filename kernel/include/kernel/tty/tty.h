//
// Created by dylan on 08/07/2026.
//

#ifndef BLU_OS_TTY_H
#define BLU_OS_TTY_H

#include <stddef.h>
#include <stdint.h>

#ifdef __x86_64__
    #define VGA_MEMORY 0xFFFFFFFF800B8000
#elif
    #define VGA_MEMORY 0xb8000
#endif

void terminalInit();

void terminalSetColor(uint8_t color);

void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y);

void terminalScroll();

void terminalPutChar(char c);

void terminalWrite(const char* data, size_t size);

void terminalWriteString(const char* data);

#endif //BLU_OS_TTY_H
