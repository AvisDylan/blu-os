/**
 * @file scheduler.h
 *
 * @author Avis
 * */

#ifndef BLU_OS_SCHEDULER_H
#define BLU_OS_SCHEDULER_H

#include <kernel/thread/thread.h>

void schedulerInit(void);
void schedulerAddThread(Thread* thread);
void schedulerRemoveThread(Thread* thread);
void schedulerYield(void);
void schedulerExitCurrent(void);
void threadTrampoline(void);
Thread* getCurrentThread(void);

#endif
