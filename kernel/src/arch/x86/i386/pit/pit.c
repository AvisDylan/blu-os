#include <arch/x86/i386/io/io.h>
#include <arch/x86/i386/pit/pit.h>
#include <stdint.h>

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND 0x43
#define PIT_BASE_FREQ 1193182

static uint32_t pitFrequency = 100;
static volatile uint64_t systemTicks = 0;

void pitInit(uint32_t freqHz) {
    pitFrequency = freqHz;

    uint32_t divisor = PIT_BASE_FREQ / freqHz;

    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL0, divisor & 0xff);
    outb(PIT_CHANNEL0, (divisor >> 8) & 0xff);
}

void timerTick(void) { systemTicks++; }

uint64_t timerGetTicks(void) { return systemTicks; }

uint64_t timerGetMs(void) { return systemTicks * (1000 / pitFrequency); }
