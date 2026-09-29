/**
 * @author Avis
 *
 * @file process.h
 *
 * Userspace processes
 * */

#ifndef BLU_OS_PROCESS_H
#define BLU_OS_PROCESS_H

#include <arch/x86/i386/mmu/physicalmemorymanager.h>
#include <arch/x86/i386/syscall/syscall.h>
#include <kernel/thread/thread.h>
#include <stdint.h>
#include <sys/types.h>

#define PROCESS_RUNNING 0
#define PROCESS_SLEEPING 1
#define PROCESS_ZOMBIE 2

#define PROCESS_MAX_FDS 16
#define PROCESS_MAX_NAME 64

typedef struct {
    int present;
} FileDescriptor;

typedef struct process {
    pid_t pid;
    pid_t parentPid;
    uint8_t state;
    uint8_t exitCode;
    struct process* parent;
    struct process* children;
    struct process* sibling;
    struct process* next;
    physical_addr_t pageDirectory;
    FileDescriptor fileDescriptorTable[PROCESS_MAX_FDS];
    Thread* mainThread;
    char name[PROCESS_MAX_NAME];
} Process;

void processInit(void);
Process* processCreateKernel(void);
Process* processFork(Process* parent, SyscallFrame* frame);
void processExecve(Process* process, const char* path, char* const argv[], char* const envp[], SyscallFrame* frame);
void processExit(Process* process, uint8_t code);
pid_t processWaitPid(Process* process, pid_t pid, int* status, int options);
void processReap(Process* process);
Process* processGetCurrent(void);
Process* processFindByPid(pid_t pid);
pid_t processAllocPid(void);

#endif
