#include "buttons.h"
#include "screens.h"

enum button_pin {
    BET_PLUS    = BIT5,
    BET_MINUS   = BIT6,
    PLAY        = BIT0,
    CASH_OUT    = BIT7,
    BUTTON_PINS = BET_PLUS | BET_MINUS | PLAY | CASH_OUT,
};

/*
init_buttons
Initializes the information used by the buttons
Inputs: None
Outputs: None
Side Effects: Changes pins and interrupt handlers
*/
void init_buttons() {
    flag_bet_plus = 0;
    flag_bet_minus = 0;
    flag_play = 0;
    flag_cash_out = 0;

    // GPIO
    P1SEL1  &= ~BUTTON_PINS;
    P1SEL0  &= ~BUTTON_PINS;
    // Direction: In
    P1DIR   &= ~BUTTON_PINS;
    P1REN   |=  BUTTON_PINS;            // enable internal resistor
    P1OUT   |=  BUTTON_PINS;            // enable pull-up resistor (output high)
    P1IES   |=  BUTTON_PINS;            // set pin interrupt to trigger when it goes from high to low
    P1IE    |=  BUTTON_PINS;            // enable interrupt
    P1IFG   =   0;                      // Clear all P1 interrupt flags

    NVIC->ISER[(PORT1_IRQn)/32] = 1 << (PORT1_IRQn % 32);
    if (NVIC_GetEnableIRQ(PORT1_IRQn)) {
        printf("PORT1 IRQ enabled \n");
    } else {
        printf("[ERROR]: PORT1 IRQ not enabled \n!");
    }
}

/*
PORT1_IRQHandler
Interrupt handler for BET_PLUS, BET_MINUS, PLAY and CASH OUT buttons
Inputs: None
Outputs: None
Side Effects: Changes flags representing whether interrupt fired.
*/
void PORT1_IRQHandler() {
    if (P1IFG & BET_PLUS) {
        if (on_game_screen == ON) {
            flag_bet_plus = 1;
        }
        P1IFG &= ~BET_PLUS;
    } else if (P1IFG & BET_MINUS) {
        if (on_game_screen == ON) {
            flag_bet_minus = 1;
        }
        P1IFG &= ~BET_MINUS;
    } else if (P1IFG & PLAY) {
        flag_play = 1;
        P1IFG &= ~PLAY;
    } else if (P1IFG & CASH_OUT) {
        flag_cash_out = 1;
        P1IFG &= ~CASH_OUT;
    }
}
