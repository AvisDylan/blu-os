//
// Created by dylan on 17/07/2026.
//

#ifndef BLU_OS_HAL_H
#define BLU_OS_HAL_H

void kalInitGdt(void);

void kalInitIdt(void);

void kalInitPhysicalMemoryManager(size_t memSizeInMb);

void kalInitVirtualMemoryManager(void);

#endif //BLU_OS_HAL_H
