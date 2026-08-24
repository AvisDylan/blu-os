#include <kernel/libk/stdlib.h>
#include <kernel/thread/thread.h>

#include "arch/kal.h"

static tid_t nextTid = 1;

/**
 * @brief Creates a new thread.
 *
 * @param entry Function pointer to thread entry point.
 * @param stackSize Size of stack for thread in bytes.
 * @return Pointer to created thread or NULL on failure.
 */
Thread* createThread(thread_entry_t entry, size_t stackSize) {
    Thread* t = (Thread*) kmalloc(sizeof(Thread));

    if (!t)
        return NULL;

    t->tid = nextTid++;
    t->entryPoint = entry;
    t->state = THREAD_RUNNABLE;
    t->stackSize = stackSize;

    t->kernelStack = kmalloc(stackSize);

    if (!t->kernelStack) {
        kfree(t);

        return NULL;
    }

    t->stackPointer = (void*) ((uintptr_t) t->kernelStack + stackSize);

    kalThreadSetupStack(t);

    return t;
}

Thread* threadCurrent();
