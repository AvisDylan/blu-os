//
// Created by dylan on 17/07/2026.
//

#include <arch/x86/i386/gdt/gdt.h>
#include <arch/x86/i386/idt/idt.h>
#include <arch/x86/i386/mmu/physicalmemorymanager.h>
#include <arch/x86/i386/mmu/virtualmemorymanager.h>
#include <kernel/thread/thread.h>
#include <stddef.h>

void kalInitGdt() { initGdt(); }

void kalInitIdt() { initIdt(); }

void kalInitPhysicalMemoryManager(size_t memSizeInMb) { initPhysicalMemoryManager(memSizeInMb); }

void kalInitVirtualMemoryManager() { initVirtualMemoryManager(); }

void kalThreadSetupStack(Thread* t) {
    uint32_t* stackPointer = (uint32_t*) t->stackPointer;
    stackPointer -= 5;

    stackPointer[0] = (uint32_t) t->entryPoint; // This will be popped as EIP by ret
    stackPointer[1] = 0; // EBP
    stackPointer[2] = 0; // EBX
    stackPointer[3] = 0; // ESI
    stackPointer[4] = 0;

    t->stackPointer = (void*) stackPointer;
}
