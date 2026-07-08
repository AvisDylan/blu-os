#include <kernel/tty/tty.h>
#include <stdio.h>

void kernelMain() {
    terminalInit();
    printf("Hello World!\n");
}
