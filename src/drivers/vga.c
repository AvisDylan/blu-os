//
// Created by dylan on 07/07/2026.
//

#include <stddef.h>
#include <stdint.h>

#include <drivers/vga.h>

#define VGA_MEMORY 0xb8000

static size_t terminalRow;
static size_t terminalColumn;
static uint8_t terminalColor;
static uint16_t* terminalBuffer = (uint16_t*) VGA_MEMORY;

size_t strlen(const char* str) {
    size_t length = 0;

    while (str[length])
        length++;

    return length;
}

uint8_t vgaEntryColor(enum VGAColor fg, enum VGAColor bg) {
    return fg | bg << 4;
}

uint16_t vgaEntry(uint8_t uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

void terminalInit() {
    terminalRow = 0;
    terminalColumn = 0;
    terminalColor = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;

            terminalBuffer[index] = vgaEntry(' ', terminalColor);
        }
    }
}

void terminalSetColor(uint8_t color) {
    terminalColor = color;
}

void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;

    terminalBuffer[index] = vgaEntry(c, color);
}

void terminalScroll() {
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t srcIndex = y * VGA_WIDTH + x;
            const size_t dstIndex = (y - 1) * VGA_WIDTH + x;

            terminalBuffer[dstIndex] = terminalBuffer[srcIndex];
        }
    }

    size_t lastRowIndex = (VGA_HEIGHT - 1) & VGA_WIDTH;

    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminalBuffer[lastRowIndex + x] = vgaEntry(' ', terminalColor);
    }
}

void terminalPutChar(char c) {
    if (c == '\n') {
        terminalColumn = 0;

        if (++terminalRow == VGA_HEIGHT) {
            terminalScroll();
            terminalRow = VGA_HEIGHT - 1;
        }

        return;
    }

    if (c == '\r') {
        terminalColumn = 0;
        return;
    }

    if (c == '\t') {
        terminalColumn = (terminalColumn + 4) & ~3;

        if (terminalColumn >= VGA_WIDTH) {
            terminalColumn = 0;

            if (++terminalRow == VGA_HEIGHT) {
                terminalScroll();
                terminalRow = VGA_HEIGHT - 1;
            }
        }
        return;
    }

    terminalPutEntryAt(c, terminalColor, terminalColumn, terminalRow);

    if (++terminalColumn == VGA_WIDTH) {
        terminalColumn = 0;

        if (++terminalRow == VGA_HEIGHT) {
            terminalScroll();
            terminalRow = VGA_HEIGHT - 1;
        }
    }
}

void terminalWrite(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminalPutChar(data[i]);
    }
}

void terminalWriteString(const char* data) {
    terminalWrite(data, strlen(data));
}
