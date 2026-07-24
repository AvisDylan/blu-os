//
// Created by dylan on 17/07/2026.
//

#include <stddef.h>
#include <arch/x86/amd64/gdt/gdt.h>
#include <arch/x86/amd64/idt/idt.h>
#include <kernel/thread/thread.h>

void kalInitGdt() {
    initGdt();
}

void kalInitIdt() {
    initIdt();
}

void kalInitPhysicalMemoryManager(size_t memSizeInMb) {

}

void kalInitVirtualMemoryManager() {

}

void kalThreadSetupStack(thread_t* t) {
    uint64_t* stackPointer = (uint64_t*) t->stackPointer;
    stackPointer -= 7;

    stackPointer[0] = (uint64_t)t->entryPoint;
    stackPointer[1] = 0;
    stackPointer[2] = 0;
    stackPointer[3] = 0;
    stackPointer[4] = 0;
    stackPointer[5] = 0;
    stackPointer[6] = 0;

    t->stackPointer = (void*) stackPointer;
}