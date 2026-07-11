//
// Created by dylan on 11/07/2026.
//

#include <stdint.h>
#include <arch/i386/io/io.h>

void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

uint8_t inb(uint16_t port) {
    uint8_t result;

    asm volatile("inb %w1, %b0" : "=a"(result) : "Nd"(port) : "memory");

    return result;
}

void ioWait() {
    outb(0x80, 0);
}
