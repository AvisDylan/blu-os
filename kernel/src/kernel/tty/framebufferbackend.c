/**
 * @author Avis
 *
 * @file framebufferbackend.c
 *
 * Framebuffer backend for terminal
 * */

#include <drivers/vga.h>
#include <kernel/tty/tty.h>
#include <kernel/tty/vgabackend.h>
#include <stdint.h>
#include "drivers/framebuffer.h"
#include "kernel/tty/font8x16.h"

#define GLYPH_WIDTH 8
#define GLYPH_HEIGHT 16

static const uint32_t vgaPalette[16] = {
        0x000000, 0x0000AA, 0x00AA00, 0x00AAAA, 0xAA0000, 0xAA00AA, 0xAA5500, 0xAAAAAA,
        0x555555, 0x5555FF, 0x55FF55, 0x55FFFF, 0xFF5555, 0xFF55FF, 0xFFFF55, 0xFFFFFF,
};

static Framebuffer* framebuffer;

static void framebufferPutEntryAt(size_t column, size_t row, char c, uint8_t color) {
    uint32_t foreRgb = vgaPalette[color & 0x0f];
    uint32_t backRgb = vgaPalette[(color >> 4) & 0x0f];

    const uint8_t* glyph = font8x16[(uint8_t) c];
    uint32_t pX = (uint32_t) column * GLYPH_WIDTH;
    uint32_t pY = (uint32_t) row * GLYPH_HEIGHT;

    for (uint32_t r = 0; r < GLYPH_HEIGHT; r++) {
        uint8_t bits = glyph[r];

        for (uint32_t bitCol = 0; bitCol < GLYPH_WIDTH; bitCol++) {
            uint32_t rgb = (bits & (0x80 >> bitCol)) ? foreRgb : backRgb;

            framebufferPutPixel(framebuffer, pX + bitCol, pY + r, rgb);
        }
    }
}

static void framebufferScroll1(uint8_t color) { // 1 to avoid name collision
    (void) color;

    framebufferScroll(framebuffer, GLYPH_HEIGHT);
}

static void framebufferClear1(uint8_t color) { framebufferClear(framebuffer, vgaPalette[(color >> 4) & 0x0f]); }

void framebufferBackendGet(Framebuffer* fb, TerminalBackend* terminal) {
    framebuffer = fb;

    terminal->putEntryAt = framebufferPutEntryAt;
    terminal->clear = framebufferClear1;
    terminal->scroll = framebufferScroll1;
    terminal->columns = framebuffer->width / GLYPH_WIDTH;
    terminal->rows = framebuffer->height / GLYPH_HEIGHT;
}
