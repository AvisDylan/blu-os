#include <arch/x86/i386/syscall/syscall.h>
#include <kernel/libk/stdio.h>

void syscallDispatch(SyscallFrame* syscallFrame) {
    kprintf("Syscall code: %u\n", syscallFrame->eax);

    switch (syscallFrame->eax) {
        case 60: // sys exit
            kprintf("Exit code: %i\n", syscallFrame->ebx);
            break;
    }
}
