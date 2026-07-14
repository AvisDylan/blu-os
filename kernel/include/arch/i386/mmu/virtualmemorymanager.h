//
// Created by dylan on 14/07/2026.
//

#ifndef BLU_OS_VIRTUALMEMORYMANAGER_H
#define BLU_OS_VIRTUALMEMORYMANAGER_H

#include <stdint.h>

#define PAGE_PRESENT 0x1
#define PAGE_WRITE 0x2
#define PAGE_USER 0x4

void initVirtualMemoryManager();

void mapPage(uint32_t virtualAddress, uint32_t physicalAddress, uint32_t flags);

#endif //BLU_OS_VIRTUALMEMORYMANAGER_H
