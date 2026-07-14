//
// Created by dylan on 13/07/2026.
//

#ifndef BLU_OS_PAGING_H
#define BLU_OS_PAGING_H

#include <stdint.h>

extern void loadPageDirectory(uint32_t* directory);

extern void enablePaging();

#endif //BLU_OS_PAGING_H
