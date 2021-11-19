#include "msp.h"

#define BC 6 // idk how the math works but 6 should be enough for 3 blinks
#define SYSTICK_HZ 3000000

/**
 * main.c
 */
enum color_t{
    RED = 0,
    GREEN = 1,
    YELLOW = 2
};

unsigned int i;
volatile enum color_t flag;
volatile uint32_t timeout = 1;
volatile uint32_t blink_count = 0;

// Duty cycle in units of 0.1% (1 thousandths)
uint32_t duty_cycle_thousandths = 200;

void PORT1_IRQHandler(void);
void SysTick_Init_interrupt(void);
void SysTick_Handler(void);

/*
Main function
Inputs: None
Outputs: None
Side Effects: Executes program
*/
void main(void) {
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    // Port 1 Setup for interrupt
    P1 -> SEL0 &=~ BIT1;
    P1 -> SEL1 &=~ BIT1;
    P1 -> DIR  &=~ BIT1;
    P1 -> REN |= BIT1;          // enable internal resistor
    P1 -> OUT |= BIT1;          // enable pull-up resistor (P1.1 output high)
    P1 -> IES |= BIT1;          // set pin interrupt to trigger when it goes from high to low
    P1 -> IE  |= BIT1;          // enable interrupt for P1.1
    P1 -> IFG = 0;              // Clear all P1 interrupt flags

    P1 -> SEL0 &=~ BIT4;
    P1 -> SEL1 &=~ BIT4;
    P1 -> DIR  &=~ BIT4;
    P1 -> REN |= BIT4;          // enable internal resistor
    P1 -> OUT |= BIT4;          // enable pull-up resistor (P1.4 output high)
    P1 -> IES |= BIT4;          // set pin interrupt to trigger when it goes from high to low
    P1 -> IE  |= BIT4;          // enable interrupt for P1.4
    P1 -> IFG = 0;              // Clear all P1 interrupt flags

    // Set the pins as output through the LEDs
    P2DIR |= BIT0;                        // P2.0 set as output
    P2DIR |= BIT1;                        // P2.1 set as output
    P2DIR |= BIT2;                        // P2.2 set as output

    flag = RED;

    SysTick_Init_interrupt();
    NVIC_EnableIRQ(PORT1_IRQn);
    if (NVIC_GetEnableIRQ(PORT1_IRQn)) {
        printf("PORT1 IRQ enabled \n");
    }
    __enable_irq();

    while(1) {
        //~~~~~~~~~~~~~~~~~~~LED BLINKING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if(timeout) {
            switch ((enum color_t) flag) {
                case RED:
                    /* code */
                    P2 -> OUT ^= BIT0;  // RED LED TURNING ON AND OFF
                    break;
                case GREEN:
                    P2 -> OUT ^= BIT1;  // GREEN LED TURNING ON AND OFF
                    flag = (--blink_count) ? GREEN : RED;
                    break;
                case YELLOW:
                    P2 -> OUT ^= BIT0;
                    P2 -> OUT ^= BIT1;  // YELLOW LED TURNING ON AND OFF
                    flag = (--blink_count) ? YELLOW : RED;
                    break;
                default:
                    break;
            }
            timeout = 0;
        }
    }
}

/*
Initialize Systick
Inputs: None
Outputs: None
Side Effects: Changes Systick registers
*/
void SysTick_Init_interrupt(void){
    SysTick -> CTRL = 0;            // disable SysTick During step
    SysTick -> LOAD = SYSTICK_HZ/2;      // reload value of 0.5s interrupts
    SysTick -> VAL = 0;             // any write to current clears it
    SysTick -> CTRL = 0x00000007;   // enable systic, 3Mhz, Interrupts
}

/*
Interrupt handler to handle Systick firing
Inputs: None
Outputs: None
Side Effects: Changes the global variable tracking Systick
*/
void SysTick_Handler(void){
    timeout = 1;                    // set flag for timeout of SysTick, rest in main
}

/*
Interrupt handler to handle PORT1 Interrupts
Inputs: None
Outputs: None
Side Effects: Changes P1.1 and P1.4 interrupt flags, changes the blink 
    count and the color to blink
*/
void PORT1_IRQHandler(void) {
    if(blink_count > 0) {       // if currently blinking, keep blinking but decrement
        P1IFG &= ~BIT1;         // Reset the interrupt flag
        P1IFG &= ~BIT4;         // Reset the interrupt flag
        return;
    }

    if(P1IFG & BIT1) {   // user has pressed on pin 1.1
        P2->OUT &= 0x0;                     // Clear all the bits on the register (set them to off) and prepare for green
        flag = GREEN;
        blink_count = BC;
    } else if (P1IFG & BIT4){   // user has pressed on pin 1.4
        P2->OUT &= 0x0;                     // Clear all the bits on the register (set them to off) and prepare for blue
        flag = YELLOW;
        blink_count = BC;
    } else {
        flag = RED;
    }

    P1IFG &= ~BIT1;         // Reset the interrupt flag
    P1IFG &= ~BIT4;         // Reset the interrupt flag
}

