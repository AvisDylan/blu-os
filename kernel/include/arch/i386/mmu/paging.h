//
// Created by dylan on 13/07/2026.
//

#ifndef BLU_OS_PAGING_H
#define BLU_OS_PAGING_H

#include <stdint.h>

#define PAGE_PRESENT 0x1
#define PAGE_WRITE 0x2
#define PAGE_USER 0x4

extern void loadPageDirectory(uint32_t* directory);

extern void enablePaging();

void initPaging();

#endif //BLU_OS_PAGING_H
