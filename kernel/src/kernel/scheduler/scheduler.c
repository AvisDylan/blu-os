/**
 * @file scheduler.c
 *
 * @author Avis
 * */

#include "kernel/scheduler/scheduler.h"
#include <kernel/thread/thread.h>
#include <stddef.h>

static Thread* currentThread = NULL;
static Thread* queueHead = NULL;

/**
 * @author Avis
 *
 * @brief Initializes scheduler
 * */
void schedulerInit(void) {
    static Thread kernelThread;

    kernelThread.tid = 0;
    kernelThread.state = THREAD_RUNNABLE;
    kernelThread.next = &kernelThread;

    currentThread = &kernelThread;
    queueHead = &kernelThread;
}

/**
 * @author Avis
 *
 * @brief Adds thread to scheduler queue
 * */
void schedulerAddThread(Thread* thread) {
    thread->next = currentThread->next;
    currentThread->next = thread;
}

void schedulerYield(void) {
    Thread* prev = currentThread;
    Thread* next = prev->next;

    while (next->state == THREAD_EXITED && next != prev) {
        next = next->next;
    }

    if (next == prev)
        return;

    currentThread = next;

    threadSwitch(prev, next);
}

void schedulerExitCurrent(void) {
    currentThread->state = THREAD_EXITED;

    schedulerYield();

    for (;;) {
        asm volatile("hlt");
    }
}

void threadTrampoline(void) {
    Thread* thread = getCurrentThread();
    thread->entryPoint();
    schedulerExitCurrent();
}

/**
 * @author Avis
 *
 * @brief Returns current thread of scheduler
 *
 * @return Pointer to current thread
 * */
Thread* getCurrentThread(void) { return currentThread; }
