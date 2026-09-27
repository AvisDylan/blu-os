#ifndef BLU_OS_SYSCALL_H
#define BLU_OS_SYSCALL_H

#include <stdint.h>

// syscall numbers https://www.chromium.org/chromium-os/developer-library/reference/linux-constants/syscalls/

typedef struct {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
} SyscallFrame;

void syscallHandler(void);
void syscallDispatch(SyscallFrame* syscallFrame);

#endif
