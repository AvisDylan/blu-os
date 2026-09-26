/**
 * @author Avis
 *
 * @file framebuffer.h
 *
 * BIOS VBE framebuffer driver
 * */

#ifndef BLU_OS_FRAMEBUFFER_H
#define BLU_OS_FRAMEBUFFER_H

#include <arch/x86/boot/multiboot.h>
#include <stdint.h>

typedef struct {
    uint8_t* address;
    uint32_t pitch;
    uint32_t width;
    uint32_t height;
    uint8_t bitsPerPixel;
} Framebuffer;

void framebufferInit(MultibootInfo* multibootInfo, Framebuffer* framebuffer);

void framebufferPutPixel(Framebuffer* framebuffer, uint32_t x, uint32_t y, uint32_t rgb);

void framebufferClear(Framebuffer* framebuffer, uint32_t rgb);

void framebufferScroll(Framebuffer* framebuffer, uint32_t rows);

#endif
