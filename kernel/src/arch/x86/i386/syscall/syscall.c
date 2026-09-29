#include <arch/x86/i386/syscall/syscall.h>
#include <kernel/libk/stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include "kernel/process/process.h"

void syscallDispatch(SyscallFrame* syscallFrame) {
    kprintf("Syscall code: %u\n", syscallFrame->eax);

    switch (syscallFrame->eax) {
        case EXIT:
            processExit(processGetCurrent(), (uint8_t) syscallFrame->ebx);
            break;
        case FORK:
            Process* child = processFork(processGetCurrent(), syscallFrame);
            syscallFrame->eax = child ? child->pid : -1;
            break;
        case WAIT_PID:
            syscallFrame->eax = (uint32_t) processWaitPid(processGetCurrent(), (pid_t) syscallFrame->ebx,
                                                          (int*) syscallFrame->ecx, (int) syscallFrame->edx);
            break;
        case EXECVE:
            processExecve(processGetCurrent(), (const char*) syscallFrame->ebx, (char* const*) syscallFrame->ecx,
                          (char* const*) syscallFrame->edx, syscallFrame);
            break;
    }
}
