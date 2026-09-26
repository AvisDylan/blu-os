/**
 * @author Avis
 *
 * @file rtc.h
 *
 *
 * */

#ifndef BLU_OS_RTC_H
#define BLU_OS_RTC_H

#include <stdint.h>

typedef struct {
    uint16_t year;
    uint8_t month, day, hour, minute, second;
} RtcTime;

uint64_t rtcReadUnixTime(void);

#endif
