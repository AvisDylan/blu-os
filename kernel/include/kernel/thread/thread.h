#ifndef BLU_OS_THREAD_H
#define BLU_OS_THREAD_H

#include <stddef.h>
#include <stdint.h>

#define THREAD_RUNNABLE 1
#define THREAD_EXITED 2

typedef uint32_t tid_t;
typedef int (*thread_entry_t)(void);
typedef struct thread {
    tid_t tid;
    void* kernelStack;
    size_t stackSize;
    void* stackPointer;
    thread_entry_t entryPoint;
    uint8_t state;
    struct thread* next;
} Thread;

extern void threadSwitch(Thread* from, Thread* to);

Thread* createThread(thread_entry_t entry, size_t stackSize);

#endif
