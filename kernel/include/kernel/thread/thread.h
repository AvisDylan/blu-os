#ifndef BLU_OS_THREAD_H
#define BLU_OS_THREAD_H

#include <arch/x86/i386/syscall/syscall.h>
#include <stddef.h>
#include <stdint.h>

#define THREAD_RUNNABLE 1
#define THREAD_SLEEPING 2
#define THREAD_EXITED 3

struct process;

typedef uint32_t tid_t;
typedef int (*thread_entry_t)(void);
typedef struct thread {
    tid_t tid;
    void* kernelStack;
    size_t stackSize;
    void* stackPointer;
    thread_entry_t entryPoint;
    uint8_t state;
    struct process* process;
    SyscallFrame context;
    struct thread* next;
} Thread;

extern void threadSwitch(Thread* from, Thread* to);
extern void threadRestoreContext(void);

Thread* createThread(thread_entry_t entry, size_t stackSize);
Thread* createThreadFrom(Thread* parent, const SyscallFrame* syscallFrame, uint32_t eax);
void destroyThread(Thread* thread);

#endif
