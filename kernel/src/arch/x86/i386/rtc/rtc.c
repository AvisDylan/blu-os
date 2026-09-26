#include <arch/x86/i386/rtc/rtc.h>
#include <stdint.h>
#include "arch/x86/i386/io/io.h"

#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

static uint8_t cmosRead(uint8_t reg) {
    outb(CMOS_ADDRESS, reg);
    return inb(CMOS_DATA);
}

static int cmosUpdateInProgress(void) {
    outb(CMOS_ADDRESS, 0x0a);
    return inb(CMOS_DATA) & 0x80;
}

static uint8_t bcdToBin(uint8_t val) { return (val & 0x0F) + ((val / 16) * 10); }

static void rtcReadRaw(RtcTime* out) {
    while (cmosUpdateInProgress()) {
    }

    uint8_t second = cmosRead(0x00);
    uint8_t minute = cmosRead(0x02);
    uint8_t hour = cmosRead(0x04);
    uint8_t day = cmosRead(0x07);
    uint8_t month = cmosRead(0x08);
    uint8_t year = cmosRead(0x09);
    uint8_t regB = cmosRead(0x0b);

    if (!(regB & 0x04)) {
        second = bcdToBin(second);
        minute = bcdToBin(minute);
        hour = bcdToBin(hour & 0x7f);
        day = bcdToBin(day);
        month = bcdToBin(month);
        year = bcdToBin(year);
    }

    if (!(regB & 0x02) && (hour & 0x80))
        hour = ((hour & 0x7F) + 12) % 24;

    out->second = second;
    out->minute = minute;
    out->hour = hour;
    out->day = day;
    out->month = month;
    out->year = 2000 + year;
}

// https://howardhinnant.github.io/date_algorithms.html
static uint64_t daysFromCivil(int year, int month, int day) {
    year -= month <= 2;
    int era = (year >= 0 ? year : year - 399) / 400;
    unsigned yoe = (unsigned) (year - era * 400);
    unsigned doy = (153 * (month > 2 ? month - 3 : month + 9) + 2) / 5 + day - 1;
    unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;

    return era * 146097 + (int) doe - 719468;
}

uint64_t rtcReadUnixTime(void) {
    RtcTime time;

    rtcReadRaw(&time);

    uint64_t days = daysFromCivil(time.year, time.month, time.day);

    return days * 86400ULL + time.hour * 3600ULL + time.minute * 60ULL + time.second;
}
