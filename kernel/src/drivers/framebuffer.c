#include <arch/x86/i386/mmu/physicalmemorymanager.h>
#include <arch/x86/i386/mmu/virtualmemorymanager.h>
#include <drivers/framebuffer.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

void framebufferInit(MultibootInfo* multibootInfo, Framebuffer* framebuffer) {
    if (multibootInfo->framebufferType != 1)
        return;

    framebuffer->pitch = multibootInfo->framebufferPitch;
    framebuffer->width = multibootInfo->framebufferWidth;
    framebuffer->height = multibootInfo->framebufferHeight;
    framebuffer->bitsPerPixel = multibootInfo->framebufferBpp;

    uint32_t physicalAddress = (uint32_t) multibootInfo->framebufferAddr;
    size_t size = (size_t) framebuffer->pitch * framebuffer->height;
    uint32_t pageCount = (size + PAGE_SIZE - 1) / PAGE_SIZE;

    for (uint32_t i = 0; i < pageCount; i++) {
        uint32_t address = physicalAddress + i * PAGE_SIZE;
        mapPage(address, address, PAGE_WRITE);
    }

    framebuffer->address = (uint8_t*) physicalAddress;
}

void framebufferPutPixel(Framebuffer* framebuffer, uint32_t x, uint32_t y, uint32_t rgb) {
    if (x >= framebuffer->width || y >= framebuffer->height)
        return;

    uint8_t* row = framebuffer->address + (size_t) y * framebuffer->pitch;

    *(uint32_t*) (row + x * (framebuffer->bitsPerPixel / 8)) = rgb;
}

void framebufferClear(Framebuffer* framebuffer, uint32_t rgb) {
    for (uint32_t y = 0; y < framebuffer->height; y++) {
        for (uint32_t x = 0; x < framebuffer->width; x++) {
            framebufferPutPixel(framebuffer, x, y, rgb);
        }
    }
}

void framebufferScroll(Framebuffer* framebuffer, uint32_t rows) {
    size_t row = (size_t) framebuffer->pitch * rows;
    size_t total = (size_t) framebuffer->pitch * framebuffer->height;

    memmove(framebuffer->address, framebuffer->address + row, total - row);
    memset(framebuffer->address + total - row, 0, row);
}
