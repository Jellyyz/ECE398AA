#ifndef MAIN_H
#define MAIN_H

#include "util.h"

/*
Pin mapping:

LCD: 6.0, 6.1, 6.4, 6.5, 6.6, 6.7
Keypad: 4.0, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6
LEDs: Red - 2.0, Green - 2.1 (Remove jumpers for these 2)
Piezzo sounder: 2.7 (TA0.4)
7-segment display 1: 2.3, 2.4, 2.5, 2.6, 3.0, 3.2, 3.3
7-segment display 2: 5.0, 5.1, 5.2, 5.4, 5.5, 5.6, 5.7
Decimal points disconnected so only 7 pins needed.
Push buttons:
    Play: 1.0, (RED)
    Bet+: 1.5, (GREEN)
    Bet-: 1.6, (BLACK)
    Cash Out: 1.7 (WHITE)
Port 1.0 requires removing a jumper
IR sensor: 4.7 (A6)
IR emitter: 3.5
*/

void init_peripherals(void);



#endif /* MAIN_H */
