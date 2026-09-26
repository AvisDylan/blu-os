/**
 * @author Avis
 *
 * @file framebufferbackend.h
 *
 * Framebuffer backend for terminal
 * */

#ifndef BLU_OS_FRAMEBUFFERBACKEND_H
#define BLU_OS_FRAMEBUFFERBACKEND_H

#include <drivers/framebuffer.h>
#include <kernel/tty/ttybackend.h>

void framebufferBackendGet(Framebuffer* fb, TerminalBackend* terminal);

#endif
