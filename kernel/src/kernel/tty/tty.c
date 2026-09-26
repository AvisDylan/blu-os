//
// Created by dylan on 08/07/2026.
//

#include <drivers/framebuffer.h>
#include <drivers/vga.h>
#include <kernel/tty/tty.h>
#include <stddef.h>
#include <stdint.h>
#include "arch/x86/boot/multiboot.h"
#include "kernel/tty/framebufferbackend.h"
#include "kernel/tty/vgabackend.h"

static TerminalBackend backend;
static size_t terminalRow;
static size_t terminalColumn;
static uint8_t terminalColor;

void terminalInit(MultibootInfo* multiboot) {
    static Framebuffer framebuffer;

    if (multiboot->flags & MULTIBOOT_INFO_FRAMEBUFFER)
        framebufferInit(multiboot, &framebuffer);

    if (framebuffer.address)
        framebufferBackendGet(&framebuffer, &backend);
    else
        vgaBackendGet(&backend);

    terminalRow = 0;
    terminalColumn = 0;
    terminalColor = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

    backend.clear(terminalColor);
}

void terminalSetColor(uint8_t color) { terminalColor = color; }

static void mewLine(void) {
    terminalColumn = 0;

    if (++terminalRow == backend.rows) {
        backend.scroll(terminalColor);
        terminalRow = backend.rows - 1;
    }
}

void terminalPutChar(char c) {
    if (c == '\n') {
        mewLine();
        return;
    }

    if (c == '\r') {
        terminalColumn = 0;
        return;
    }

    if (c == '\t') {
        terminalColumn = (terminalColumn + 4) & ~3;

        if (terminalColumn >= backend.columns)
            mewLine();

        return;
    }

    backend.putEntryAt(terminalColumn, terminalRow, c, terminalColor);

    if (++terminalColumn == backend.columns)
        mewLine();
}

void terminalWrite(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminalPutChar(data[i]);
    }
}

