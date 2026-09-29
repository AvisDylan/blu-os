#include <kernel/process/process.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include "arch/x86/i386/mmu/physicalmemorymanager.h"
#include "kernel/libk/stdlib.h"
#include "kernel/scheduler/scheduler.h"
#include "kernel/thread/thread.h"

static Process* processList = NULL;
static Process* kernelProcess = NULL;
static pid_t nextPid = 0;

void processInit(void) {
    kernelProcess = processCreateKernel();
    processList = kernelProcess;
}

Process* processCreateKernel(void) {
    Process* p = kmalloc(sizeof(Process));

    if (!p)
        return NULL;

    memset(p, 0, sizeof(Process));

    p->pid = processAllocPid();
    p->parentPid = 0;
    p->state = PROCESS_RUNNING;
    p->pageDirectory = getCurrentPageDirectory();

    strncpy(p->name, "kernel", PROCESS_MAX_NAME);

    Thread* t = getCurrentThread();
    t->process = p;
    p->mainThread = t;

    // stdin, stdout, stderr
    p->fileDescriptorTable[0].present = 1;
    p->fileDescriptorTable[1].present = 1;
    p->fileDescriptorTable[2].present = 1;

    return p;
}

Process* processFork(Process* parent, SyscallFrame* frame) {
    if (!parent)
        parent = processGetCurrent();

    asm volatile("cli");

    physical_addr_t childPageDir = pageDirectoryCopy(parent->pageDirectory);

    if (childPageDir == ERROR) {
        asm volatile("sti");
        return NULL;
    }

    Process* child = kmalloc(sizeof(Process));

    if (!child) {
        pageDirectoryDestroy(childPageDir);
        asm volatile("sti");
        return NULL;
    }

    memset(child, 0, sizeof(Process));

    child->pid = processAllocPid();
    child->parentPid = parent->pid;
    child->parent = parent;
    child->state = PROCESS_RUNNING;
    child->pageDirectory = childPageDir;

    strncpy(child->name, parent->name, PROCESS_MAX_NAME);

    for (uint32_t i = 0; i < PROCESS_MAX_FDS; i++) {
        child->fileDescriptorTable[i] = parent->fileDescriptorTable[i];
    }

    Thread* parentThread = getCurrentThread();
    Thread* childThread = createThreadFrom(parentThread, frame, 0);

    if (!childThread) {
        pageDirectoryDestroy(childPageDir);
        kfree(child);
        asm volatile("sti");
        return NULL;
    }

    childThread->process = child;
    child->mainThread = childThread;

    child->sibling = parent->children;
    parent->children = child;

    child->next = processList;
    processList = child;

    schedulerAddThread(childThread);

    asm volatile("sti");

    return child;
}

void processExecve(Process* process, const char* path, char* const argv[], char* const envp[], SyscallFrame* frame) {
    // TODO add elf loader and ring 3
}

void processExit(Process* process, uint8_t code) {
    if (!process)
        process = processGetCurrent();

    asm volatile("cli");
}

pid_t processWaitPid(Process* process, pid_t pid, int* status, int options);
void processReap(Process* process);
Process* processGetCurrent(void);
Process* processFindByPid(pid_t pid);
pid_t processAllocPid(void);
