/**
 * @author Avis
 *
 * @file vgabackend.c
 *
 * VGA backend for terminal
 * */

#include <drivers/vga.h>
#include <kernel/tty/tty.h>
#include <kernel/tty/vgabackend.h>
#include <stdint.h>

static uint16_t* vgaBuffer = (uint16_t*) VGA_MEMORY;

static void vgaPutEntryAt(size_t column, size_t row, char c, uint8_t color) {
    vgaBuffer[row * VGA_WIDTH + column] = vgaEntry((uint8_t) c, color);
}

static void vgaScroll(uint8_t color) {
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t srcIndex = y * VGA_WIDTH + x;
            const size_t dstIndex = (y - 1) * VGA_WIDTH + x;

            vgaBuffer[dstIndex] = vgaBuffer[srcIndex];
        }
    }

    size_t lastRowIndex = (VGA_HEIGHT - 1) * VGA_WIDTH;

    for (size_t x = 0; x < VGA_WIDTH; x++) {
        vgaBuffer[lastRowIndex + x] = vgaEntry(' ', color);
    }
}

static void vgaClear(uint8_t color) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            vgaBuffer[y * VGA_WIDTH + x] = vgaEntry(' ', color);
        }
    }
}

void vgaBackendGet(TerminalBackend* terminal) {
    terminal->putEntryAt = vgaPutEntryAt;
    terminal->clear = vgaClear;
    terminal->scroll = vgaScroll;
    terminal->columns = VGA_WIDTH;
    terminal->rows = VGA_HEIGHT;
}
