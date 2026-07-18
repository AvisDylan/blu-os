//
// Created by dylan on 17/07/2026.
//

#include <stddef.h>
#include <arch/x86/amd64/gdt/gdt.h>
#include <arch/x86/amd64/idt/idt.h>

void kalInitGdt(void) {
    initGdt();
}

void kalInitIdt(void) {
    initIdt();
}

void kalInitPhysicalMemoryManager(size_t memSizeInMb) {

}

void kalInitVirtualMemoryManager(void) {

}