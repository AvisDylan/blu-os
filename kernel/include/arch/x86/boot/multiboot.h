// Created by Avis on 24/08/2026

#ifndef BLU_OS_MULTIBOOT_H
#define BLU_OS_MULTIBOOT_H

#include <stdint.h>

#define MULTI_BOOT_MAGIC 0x2BADB002

typedef struct {
    uint32_t flags;
    uint32_t memLower;
    uint32_t memUpper;
    uint32_t bootDevice;
    uint32_t cmdline;
    uint32_t modsCount;
    uint32_t modsAddr;
    uint32_t syms[4];
    uint32_t mmapLength;
    uint32_t mmapAddr;
    uint32_t drivesLength;
    uint32_t drivesAddr;
    uint32_t configTable;
    uint32_t bootLoaderName;
    uint32_t apmTable;
    uint32_t vbeControlInfo;
    uint32_t vbeModeInfo;
    uint16_t vbeMode;
    uint16_t vbeInterfaceSeg;
    uint16_t vbeInterfaceOff;
    uint16_t vbeInterfaceLen;
    uint64_t framebufferAddr;
    uint32_t framebufferPitch;
    uint32_t framebufferWidth;
    uint32_t framebufferHeight;
    uint8_t framebufferBpp;
    uint8_t framebufferType;
} __attribute__((packed)) MultibootInfo;

#endif // BLU_OS_MULTIBOOT_H
