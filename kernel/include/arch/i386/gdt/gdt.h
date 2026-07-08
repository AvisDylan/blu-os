//
// Created by dylan on 08/07/2026.
//

#ifndef BLU_OS_GDT_H
#define BLU_OS_GDT_H
#include <stdint.h>

typedef struct {
    uint32_t base;
    uint32_t limit;
    uint8_t accesBytes;
    uint8_t flags;
} GDT;

extern void setGdt(uint16_t limit, uint32_t base);

void encodeGdtEntry(uint8_t* target, GDT source);

void initGdt();

#endif //BLU_OS_GDT_H
