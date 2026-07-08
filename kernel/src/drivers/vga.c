//
// Created by dylan on 07/07/2026.
//

#include <stddef.h>
#include <stdint.h>

#include <drivers/vga.h>

uint8_t vgaEntryColor(enum VGAColor fg, enum VGAColor bg) {
    return fg | bg << 4;
}

uint16_t vgaEntry(uint8_t uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}
