//
// Created by dylan on 11/07/2026.
//

#ifndef BLU_OS_IO_H
#define BLU_OS_IO_H
#include <stdint.h>

void outb(uint16_t port, uint8_t value);

uint8_t inb(uint16_t port);

void ioWait();

#endif //BLU_OS_IO_H
