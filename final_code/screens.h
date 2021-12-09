#ifndef SCREENS_H
#define SCREENS_H

#include "util.h"

#define BOOT_SCREEN_TIME 3

int on_game_screen;

void boot_screen(void);
void menu_main(void);
void menu_sounds(void);
void menu_enter_credits(void);
void enter_credits(void); 
void menu_play(void);
void reel(void);
void menu_cash_out(void);

void convert_credit_str(uint8_t *str1, uint32_t credit_balance);


#endif /* SCREENS_H */
