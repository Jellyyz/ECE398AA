#ifndef BUTTONS_H
#define BUTTONS_H

#include "util.h"

volatile int flag_bet_plus;
volatile int flag_bet_minus;
volatile int flag_play;
volatile int flag_cash_out;

void init_buttons(void);
void PORT1_IRQHandler(void);

#endif /* BUTTONS_H */
