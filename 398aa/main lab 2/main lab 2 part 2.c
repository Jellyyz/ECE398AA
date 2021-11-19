#include "msp.h"

# define BOUNCE_WAIT 1000
/*
Returns whether the button is pushed, accounting for switch bounce
Button input is active low. (0 for pressed, 1 for not pressed)
Inputs: None
Outputs: 1 if switch pushed, 0 if switch not pushed.
*/
int DebounceSwitch1() {
    int pin_Value = 0; // initialize variable as low
    if ((P1->IN & BIT1) == 0x00) // check if button pushed
    {
        __delay_cycles(BOUNCE_WAIT);
        if ((P1->IN & BIT1) == 0x00) // check if button is still pushed
            pin_Value = 1;
    }
    return pin_Value; // return 1 if pushed- 0 if not pushed
}

/*
Returns whether the button is released, accounting for switch bounce
Button input is active low. (0 for pressed, 1 for not pressed)
Inputs: None
Outputs: 1 if switch not pushed, 0 if switch pushed.
*/
int DebounceSwitch0() {
    int pin_Value = 0; // initialize variable as low
    if ((P1->IN & BIT1) == BIT1) // check if button pushed
    {
        __delay_cycles(BOUNCE_WAIT);
        if ((P1->IN & BIT1) == BIT1) // check if button is still pushed
            pin_Value = 1;
    }
    return pin_Value; // return 1 if pushed- 0 if not pushed
}
# undef BOUNCE_WAIT

/**
 * main.c
 */
# define ONE_S_CYCLES 3000000
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    volatile uint32_t i;

    // Set the pins as output
    P1SEL0 &= ~BIT1;                        // Configure P1.1 as simple I/O
    P1SEL1 &= ~BIT1;
    P1REN |= BIT1;                          // P1.1 pull up resistor enabled
    P1OUT |= BIT1;                          // Pull up/down is selected by P1->OUT
    P1->DIR &= ~BIT1;                       // P1.1 set as input
    P2->DIR |= BIT0;                        // P2.0 set as output
    P2->DIR |= BIT1;                        // P2.1 set as output
    P2->DIR |= BIT2;                        // P2.2 set as output
    P2->OUT &= 0x0;                         // Clear all the bits on the register (set them to off)

    // volatile uint32_t timer = 200000; // Control the time taken to blink

    // Wait for switch to be pressed so that red LED only turns on when button pressed.
    while (DebounceSwitch1() != 1);     
    
    while (1)                               // continuous loop
    {

        // Blink red
        P2->OUT ^= BIT0;
        __delay_cycles(ONE_S_CYCLES);
        while (DebounceSwitch1() != 1);     // Wait for switch to be pressed again. Otherwise LED remains red
        P2->OUT ^= BIT0;                    // Set P2.0 LED off

        // Blink green
        P2->OUT ^= BIT1;                    // Set P2.1 LED on
        __delay_cycles(ONE_S_CYCLES);
        while (DebounceSwitch1() != 1);     // Wait for switch to be pressed. Otherwise LED remains green
        P2->OUT ^= BIT1;                    // Set P2.1 LED off

        // Blink blue
        P2->OUT ^= BIT2;                    // Set P2.2 LED on
        __delay_cycles(ONE_S_CYCLES);
        while (DebounceSwitch1() != 1);     // Wait for switch to be pressed. Otherwise LED remains blue
        P2->OUT ^= BIT2;                    // Set P2.2 LED off
    }
}
# undef ONE_S_CYCLES