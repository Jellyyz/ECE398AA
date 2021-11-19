#include "msp.h"
// #include <ti/devices/msp432p4xx/driverlib/driverlib.h>
// include <driverlib.h>

# define BOUNCE_WAIT 1000
/*
Returns whether the button is pushed, accounting for switch bounce
Button input is active low. (0 for pressed, 1 for not pressed)
Inputs: None
Outputs: 1 if switch pushed, 0 if switch not pushed.
*/
int ForwardDebounceSwitch1() {
    int pin_Value = 0; // initialize variable as low
    if ((P6->IN & BIT5) == 0x00) // check if button pushed
    {
        __delay_cycles(BOUNCE_WAIT);
        if ((P6->IN & BIT5) == 0x00) // check if button is still pushed
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
int ForwardDebounceSwitch0() {
    int pin_Value = 0; // initialize variable as low
    if ((P6->IN & BIT5) == BIT5) // check if button pushed
    {
        __delay_cycles(BOUNCE_WAIT);
        if ((P6->IN & BIT5) == BIT5) // check if button is still pushed
            pin_Value = 1;
    }
    return pin_Value; // return 1 if pushed- 0 if not pushed
}
/*
Returns whether the button is pushed, accounting for switch bounce
Button input is active low. (0 for pressed, 1 for not pressed)
Inputs: None
Outputs: 1 if switch pushed, 0 if switch not pushed.
*/
int BackwardDebounceSwitch1() {
    int pin_Value = 0; // initialize variable as low
    if ((P6->IN & BIT4) == 0x00) // check if button pushed
    {
        __delay_cycles(BOUNCE_WAIT);
        if ((P6->IN & BIT4) == 0x00) // check if button is still pushed
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
int BackwardDebounceSwitch0() {
    int pin_Value = 0; // initialize variable as low
    if ((P6->IN & BIT4) == BIT4) // check if button pushed
    {
        __delay_cycles(BOUNCE_WAIT);
        if ((P6->IN & BIT4) == BIT4) // check if button is still pushed
            pin_Value = 1;
    }
    return pin_Value; // return 1 if pushed- 0 if not pushed
}
# undef BOUNCE_WAIT

/**
 * main.c
 Pin mapping:
    Green: Pin 5.2
    Yellow: Pin 1.7
    Red: Pin 5.0
    Forward Button: Pin 6.5
    Backward Button: Pin 6.4
 */
# define ONE_S_CYCLES 3000000
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    volatile uint32_t i;
    
    // Set the pins
    // Forward Button
    P6SEL0 &= ~BIT5;                        // Configure as simple I/O
    P6SEL1 &= ~BIT5;
    P6REN |= BIT5;                          // Enable internal resistor
    P6OUT |= BIT5;                          // Enable pull up resistor
    P6DIR &= ~BIT5;                         // Direction: Input

    // Backward Button
    P6SEL0 &= ~BIT4;                        // Configure as simple I/O
    P6SEL1 &= ~BIT4;
    P6REN |= BIT4;                          // Enable internal resistor
    P6OUT |= BIT4;                          // Enable pull up resistor
    P6DIR &= ~BIT4;                         // Direction: Input

    // Green
    P5SEL0 &= ~BIT2;                        // Configure as simple I/O
    P5SEL1 &= ~BIT2;
    P5DIR |= BIT2;                          // Direction: Output
    P5OUT |= BIT2;                          // Set output to on - Debug
    P5OUT &= ~BIT2;                         // Set output to off
    // Yellow
    P1SEL0 &= ~BIT7;                        // Configure as simple I/O
    P1SEL1 &= ~BIT7;
    P1DIR |= BIT7;                          // Direction: Output
    P1OUT |= BIT7;                          // Set output to on - debug
    P1OUT &= ~BIT7;                         // Set output to off
    // Red
    P5SEL0 &= ~BIT0;                        // Configure as simple I/O
    P5SEL1 &= ~BIT0;
    P5DIR |= BIT0;                          // Direction: Output
    P5OUT |= BIT0;                          // Set output to on - debug
    P5OUT &= ~BIT0;                         // Set output to off

    // Wait for switch to be pressed so that green LED only turns on when button pressed.
    while (1) {
        if (ForwardDebounceSwitch1() == 1) {
            break;
        }
        if (BackwardDebounceSwitch1() == 1) {
            break;
        }
    }
    typedef enum {GREEN = 0, YELLOW = 1, RED = 2} Color;
    Color curr_color;
    curr_color = GREEN;

    while (1)                               // continuous loop
    {
        switch (curr_color) {
            case GREEN:
                P5->OUT ^= BIT2;
                __delay_cycles(ONE_S_CYCLES);
                while (1) {
                    if (ForwardDebounceSwitch1() == 1) { // Wait for switch to be pressed.
                        curr_color = YELLOW;
                        break;
                    }
                    if (BackwardDebounceSwitch1() == 1) { // Wait for switch to be pressed.
                        curr_color = RED;
                        break;
                    }
                }
                P5->OUT^= BIT2;                    // Set P2.0 LED off
                break;
            case YELLOW:
                P1->OUT ^= BIT7;                    // Set P2.1 LED on
                __delay_cycles(ONE_S_CYCLES);
                while (1) {
                    if (ForwardDebounceSwitch1() == 1) { // Wait for switch to be pressed.
                        curr_color = RED;
                        break;
                    }
                    if (BackwardDebounceSwitch1() == 1) { // Wait for switch to be pressed.
                        curr_color = GREEN;
                        break;
                    }
                }
                P1->OUT ^= BIT7;                    // Set P2.1 LED off
                break;
            case RED:
                P5->OUT ^= BIT0;                    // Set P2.2 LED on
                __delay_cycles(ONE_S_CYCLES);
                while (1) {
                    if (ForwardDebounceSwitch1() == 1) { // Wait for switch to be pressed.
                        curr_color = GREEN;
                        break;
                    }
                    if (BackwardDebounceSwitch1() == 1) { // Wait for switch to be pressed.
                        curr_color = YELLOW;
                        break;
                    }
                }
                P5->OUT ^= BIT0;                    // Set P2.2 LED off
                break;
        }

    }
}
# undef ONE_S_CYCLES
