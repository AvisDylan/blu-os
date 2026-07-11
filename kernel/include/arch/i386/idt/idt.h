//
// Created by dylan on 10/07/2026.
//

#ifndef BLU_OS_IDT_H
#define BLU_OS_IDT_H
#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
    uint16_t isrLow;
    uint16_t kernelCs;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isrHigh;
} __attribute__((packed)) IDTEntry;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) IDTR;

extern void* isrStubTable[];

extern void* irqStubTable[];

__attribute__((noreturn))
void exceptionHandler();

void idtSetDescriptor(uint8_t vector, void* isr, uint8_t flags);

void initIdt();

#endif //BLU_OS_IDT_H
