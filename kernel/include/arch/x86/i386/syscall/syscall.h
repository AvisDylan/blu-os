#ifndef BLU_OS_SYSCALL_H
#define BLU_OS_SYSCALL_H

#include <stdint.h>

// syscall numbers https://www.chromium.org/chromium-os/developer-library/reference/linux-constants/syscalls/

#define WAIT_PID 7
#define FORK 2
#define EXECVE 11
#define EXIT 1

typedef struct {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t eip, cs, eflags;
} SyscallFrame;

void syscallHandler(void);
void syscallDispatch(SyscallFrame* syscallFrame);

#endif
