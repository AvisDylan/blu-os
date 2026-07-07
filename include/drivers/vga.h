//
// Created by dylan on 07/07/2026.
//

#ifndef BLU_OS_VGA_H
#define BLU_OS_VGA_H

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum VGAColor {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15
};

size_t strlen(const char* str);

void terminalInit();

void terminalSetColor(uint8_t color);

void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y);

void terminalScroll();

void terminalPutChar(char c);

void terminalWrite(const char* data, size_t size);

void terminalWriteString(const char* data);

uint8_t vgaEntryColor(enum VGAColor fg, enum VGAColor bg);

uint16_t vgaEntry(uint8_t uc, uint8_t color);

#endif //BLU_OS_VGA_H
