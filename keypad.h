#ifndef KEYPAD_H
#define KEYPAD_H

#include "util.h"

#define NUM_CHARS_VALUE 3

enum keypad_const {
    STAR = 10,
    KEYPAD_ZERO = 11,
    POUND = 12,
    NUM_COLS = 3,
    INVALID_KEYPRESS = -1,
};

void init_keypad(void);
int8_t read_keypad(void);
int8_t get_keypad(void); 

#endif /* KEYPAD_H */
