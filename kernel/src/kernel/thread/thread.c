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
thread_t* createThread(thread_entry_t entry, size_t stackSize) {
    thread_t* t = (thread_t*) kmalloc(sizeof(thread_t));

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

thread_t* threadCurrent();
