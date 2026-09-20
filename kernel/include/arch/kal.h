//
// Created by dylan on 17/07/2026.
//

#ifndef BLU_OS_HAL_H
#define BLU_OS_HAL_H

#include <kernel/thread/thread.h>
#include <stddef.h>
#include "arch/x86/i386/mmu/physicalmemorymanager.h"

void kalInitGdt();

void kalInitIdt();

void kalInitPhysicalMemoryManager(size_t memSizeInMb);

void kalMarkRangeUsed(physical_addr_t address, size_t size);

void kalInitVirtualMemoryManager();

void kalThreadSetupStack(Thread* t);

#endif // BLU_OS_HAL_H
