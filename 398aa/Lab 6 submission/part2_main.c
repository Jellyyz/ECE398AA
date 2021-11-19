#include "msp.h"

/**
 * main.c
 */
#define MOTOR_F 40
#define SMCLK_F 3000000
#define TA_GRANULARITY_HZ 10000 // Count 0.1ms cycles (10KHz)
// How many system cycles per timerA cycle
#define TA_GRANULARITY_CYCLES ((uint16_t) (SMCLK_F/TA_GRANULARITY_HZ)) 
// How many timerA ticks per motor cycle
#define MOTOR_TA_TICKS (TA_GRANULARITY_HZ / MOTOR_F)

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;        // stop watchdog timer
    // Duty cycle in units of 0.1% (1 thousandths)
    uint32_t duty_cycle_thousandths = 100;
    uint32_t high_ticks;
    uint32_t timerA_ticks = 0; // We will use the timer A iterations to count.

    // Configure timer
    P2DIR |= BIT4; // P2.4 set TA0.1
    P2SEL0 |= BIT4;
    P2SEL1 &= ~BIT4;

    // Configure timer
    TIMER_A0->CCTL[0] = 0x00E0;
    TIMER_A0->CCR[0] = TA_GRANULARITY_CYCLES;

    // Configure PWM pin. use P6.0 for PWM
    P6DIR |= BIT0;
    P6SEL0 &= ~BIT0;
    P6SEL1 &= ~BIT0;
    P6OUT &= ~BIT0;

    // Start timer 
    TIMER_A0->CTL = 0x0214; // SMCLK, Up Mode, clear TAR to start

    // PWM loop
    while (1) {
        high_ticks = MOTOR_TA_TICKS * duty_cycle_thousandths/1000;
        while ((TIMER_A0->CCTL[0] & BIT0) != BIT0); // wait until the flag is set
        TIMER_A0->CCTL[0] &= ~BIT0;
        // Flag set, increment output. 
        timerA_ticks++;
        
        // Configure pin output
        if (timerA_ticks <= high_ticks) {
            // High
            P6OUT |= BIT0;
        } else {
            // Low
            P6OUT &= ~BIT0;
        }
        
        // Configure timer to reset every period.
        if (timerA_ticks >= MOTOR_TA_TICKS) {
            //printf("timerA_ticks : %d", timerA_ticks);
            timerA_ticks = 0;
        }
    }
}
