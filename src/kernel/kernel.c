#include "drivers/vga.h"

void kernelMain() {
    terminalInit();

    while (true) {
        terminalWriteString("Hello, World!\n");
    }
}
