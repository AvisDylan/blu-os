//
// Created by dylan on 17/07/2026.
//

#include <arch/x86/i386/gdt/gdt.h>
#include <arch/x86/i386/idt/idt.h>
#include <arch/x86/i386/mmu/physicalmemorymanager.h>
#include <arch/x86/i386/mmu/virtualmemorymanager.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/thread/thread.h>
#include <stddef.h>
#include <stdint.h>
#include "arch/x86/i386/pit/pit.h"
#include "arch/x86/i386/rtc/rtc.h"

static uint64_t bootUnixTime = 0;

void kalInitGdt() { initGdt(); }

void kalInitIdt() { initIdt(); }

void kalInitPhysicalMemoryManager(size_t memSizeInMb) { initPhysicalMemoryManager(memSizeInMb); }

void kalMarkRangeUsed(physical_addr_t address, size_t size) { markRangeUsed(address, size); }

void kalInitVirtualMemoryManager() { initVirtualMemoryManager(); }

void kalThreadSetupStack(Thread* t) {
    uint32_t* stackPointer = (uint32_t*) t->stackPointer;
    stackPointer -= 5;

    stackPointer[0] = 0;
    stackPointer[1] = 0;
    stackPointer[2] = 0;
    stackPointer[3] = 0;
    stackPointer[4] = (uint32_t) threadTrampoline;

    t->stackPointer = (void*) stackPointer;
}


void kalInitTimer(uint32_t freqHz) {
    bootUnixTime = rtcReadUnixTime();
    pitInit(freqHz);
}

uint64_t timerWallClockUnixMs(void) { return bootUnixTime * 1000ULL + timerGetMs(); }
