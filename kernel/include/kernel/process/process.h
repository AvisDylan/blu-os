/**
 * @author Avis
 *
 * @file process.h
 *
 * Userspace processes
 * */

#ifndef BLU_OS_PROCESS_H
#define BLU_OS_PROCESS_H

#include <kernel/thread/thread.h>
#include <stdint.h>
#include <sys/types.h>

typedef struct {
    pid_t pid;
    uint32_t pageDirectory;
    uintptr_t userStackTop;
    Thread* mainThread;
} Process;

#endif
