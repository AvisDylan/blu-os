/**
 * @author Avis
 *
 * @file keyboard.h
 *
 * Keyboard driver
 * */

#ifndef BLU_OS_KEYBOARD_H
#define BLU_OS_KEYBOARD_H

void keyboardInit(void);
void keyboardHandler(void);
char keyboardReadChar(void);

#endif
