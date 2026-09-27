#include <arch/x86/i386/io/io.h>
#include <drivers/keyboard.h>
#include <stdbool.h>
#include <stdint.h>
#include "kernel/libk/stdio.h"

#define DATA_PORT 0x60
#define CMD_PORT 0x64

static const char usQwertyScancodeMap[] = {
        0,    27,  '1', '2',  '3', '4', '5', '6', '7',  '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',
        't',  'y', 'u', 'i',  'o', 'p', '[', ']', '\n', 0,   'a', 's', 'd', 'f', 'g',  'h',  'j', 'k', 'l', ';',
        '\'', '`', 0,   '\\', 'z', 'x', 'c', 'v', 'b',  'n', 'm', ',', '.', '/', 0,    '*',  0,   ' ', 0};

static bool shift = false;
static char lastChar = 0;

void keyboardInit(void) {
    outb(CMD_PORT, 0xae);
    inb(DATA_PORT);
    shift = false;
    lastChar = 0;
}

void keyboardHandler(void) {
    uint8_t scancode = inb(DATA_PORT);

    // release
    if (scancode & 0x80) {
        uint8_t released = scancode & 0x7f;

        if (released == 0x2a || released == 0x36)
            shift = false;

        return;
    }

    // press
    if (scancode == 0x2a || scancode == 0x36) {
        shift = true;
        return;
    }

    if (scancode >= sizeof(usQwertyScancodeMap))
        return;

    char c = usQwertyScancodeMap[scancode];

    if (c == 0)
        return;

    // TODO implement other shift key combinations
    if (shift) {
        if (c >= 'a' && c <= 'z')
            c -= 32;
        else if (c >= '1' && c <= '9')
            c = "!@#$%^&*("[c - '1'];
        else if (c == '0')
            c = ')';
    }

    lastChar = c;

    kprintf("%c", c);
}

char keyboardReadChar(void) {
    char c = lastChar;
    lastChar = 0;
    return c;
}
