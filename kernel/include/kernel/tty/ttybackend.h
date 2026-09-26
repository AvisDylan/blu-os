/**
 * @author Avis
 *
 * @file ttybackend.h
 *
 * Terminal backend
 * */

#ifndef BLU_OS_TTYBACKEND_H
#define BLU_OS_TTYBACKEND_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    void (*putEntryAt)(size_t column, size_t row, char c, uint8_t color);
    void (*scroll)(uint8_t color);
    void (*clear)(uint8_t color);
    size_t columns;
    size_t rows;
} TerminalBackend;

#endif
