#ifndef BLU_OS_THREAD_H
#define BLU_OS_THREAD_H

#include <stddef.h>
#include <stdint.h>

#define THREAD_RUNNABLE 1
#define THREAD_EXITED 2

typedef uint32_t tid_t;
typedef int (*thread_entry_t)(void);
typedef struct {
    tid_t tid;
    void* kernelStack;
    size_t stackSize;
    void* stackPointer;
    thread_entry_t entryPoint;
    uint8_t state;
} thread_t;

extern void threadSwitch(thread_t* from, thread_t* to);

thread_t* createThread(thread_entry_t entry, size_t stackSize);

thread_t* threadCurrent();

#endif
