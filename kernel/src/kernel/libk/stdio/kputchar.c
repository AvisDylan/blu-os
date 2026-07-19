//
// Created by dylan on 08/07/2026.
//

#include <stdio.h>
#include <kernel/tty/tty.h>

int kputchar(int ic) {
    char c = (char) ic;
    terminalWrite(&c, sizeof(c));

    return ic;
}