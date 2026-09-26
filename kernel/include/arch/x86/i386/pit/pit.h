/**
 * @author Avis
 *
 * @file pit.h
 *
 *
 * */

#ifndef BLU_OS_PIT_H
#define BLU_OS_PIT_H

#include <stdint.h>

void pitInit(uint32_t freqHz);

void timerTick(void);

uint64_t timerGetTicks(void);

uint64_t timerGetMs(void);

#endif
