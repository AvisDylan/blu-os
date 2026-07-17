//
// Created by dylan on 17/07/2026.
//

#include <stddef.h>
#include <arch/x86/i386/idt/idt.h>
#include <arch/x86/i386/gdt/gdt.h>
#include <arch/x86/i386/mmu/virtualmemorymanager.h>
#include <arch/x86/i386/mmu/physicalmemorymanager.h>

void kalInitGdt(void) {
    initGdt();
}

void kalInitIdt(void) {
    initIdt();
}

void kalInitPhysicalMemoryManager(size_t memSizeInMb) {
    initPhysicalMemoryManager(memSizeInMb);
}

void kalInitVirtualMemoryManager(void) {
    initVirtualMemoryManager();
}