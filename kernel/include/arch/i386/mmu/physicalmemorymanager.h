//
// Created by dylan on 14/07/2026.
//

#ifndef BLU_OS_PHYSICALMEMORYMANAGER_H
#define BLU_OS_PHYSICALMEMORYMANAGER_H

#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096
#define FREE 0x00
#define USED 0x01
#define ERROR 0x00000000

typedef uint32_t physical_addr_t;

extern uint32_t endKernel;

void initPhysicalMemoryManager(size_t memSizeInMb);

physical_addr_t kallocFrame();

void kfreeFrame(physical_addr_t frameAddress);

#endif //BLU_OS_PHYSICALMEMORYMANAGER_H
