//
// Created by dylan on 08/07/2026.
//

#include <stdio.h>

#ifdef __is_libk
#include <kernel/tty/tty.h>
#endif

int putchar(int ic) {
#ifdef __is_libk
    char c = (char) ic;
    terminalWrite(&c, sizeof(c));
#else

#endif

    return ic;
}