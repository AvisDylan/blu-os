#include <kernel/libk/stdlib.h>
#include <kernel/thread/thread.h>

#include <arch/kal.h>
#include <arch/x86/i386/syscall/syscall.h>
#include <string.h>

static tid_t nextTid = 1;

/**
 * @brief Creates a new thread.
 *
 * @param entry Function pointer to thread entry point.
 * @param stackSize Size of stack for thread in bytes.
 *
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
    t->process = NULL;
    memset(&t->context, 0, sizeof(SyscallFrame));

    t->kernelStack = kmalloc(stackSize);

    if (!t->kernelStack) {
        kfree(t);

        return NULL;
    }

    t->stackPointer = (void*) ((uintptr_t) t->kernelStack + stackSize);

    kalThreadSetupStack(t);

    return t;
}

Thread* createThreadFrom(Thread* parent, const SyscallFrame* syscallFrame, uint32_t eax) {
    Thread* child = kmalloc(sizeof(Thread));

    if (!child)
        return NULL;

    child->tid = nextTid++;
    child->entryPoint = NULL;
    child->state = THREAD_RUNNABLE;
    child->stackSize = parent->stackSize;
    child->process = NULL;
    memcpy(&child->context, syscallFrame, sizeof(SyscallFrame));

    child->kernelStack = kmalloc(child->stackSize);

    if (!child->kernelStack) {
        kfree(child);

        return NULL;
    }

    uint32_t* sp = (uint32_t*) ((uintptr_t) child->kernelStack + child->stackSize);

    *--sp = syscallFrame->eflags;
    *--sp = syscallFrame->cs;
    *--sp = syscallFrame->eip;
    uint32_t* eipSlot = sp;

    *--sp = eax;
    *--sp = syscallFrame->ecx;
    *--sp = syscallFrame->edx;
    *--sp = syscallFrame->ebx;
    *--sp = (uint32_t) eipSlot;
    *--sp = syscallFrame->ebp;
    *--sp = syscallFrame->esi;
    *--sp = syscallFrame->edi;

    *--sp = (uint32_t) threadRestoreContext;
    *--sp = 0;
    *--sp = 0;
    *--sp = 0;
    *--sp = 0;

    child->stackPointer = sp;

    return child;
}

void destroyThread(Thread* thread) {
    if (!thread)
        return;

    if (thread->process && thread->process->mainThread == thread)
        thread->process->mainThread = NULL;

    if (thread->kernelStack)
        kfree(thread->kernelStack);

    kfree(thread);
}
