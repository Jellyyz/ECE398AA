#ifndef PIEZZO_H
#define PIEZZO_H

#include "util.h"

enum tune {
    TUNE0 = 0,
    TUNE1 = 1,
};

// Assumes A = 440Hz, using equal temperament
/*
#define C5 523.25
#define E5 659.25
#define G5 783.99
#define GSH5 830.61
#define B5 987.77
#define C6 1046.50
#define E6 1318.51
*/
enum note {
    C5      = 0, 
    E5      = 1, 
    G5      = 2, 
    GSH5    = 3, 
    B5      = 4, 
    C6      = 5, 
    E6      = 6,
};

void init_piezzo(void);
void on_piezzo(void);
void off_piezzo(void);
void set_note(enum note);
void set_tune(enum tune);
void play_tune(void);

#endif /* PIEZZO_H */
