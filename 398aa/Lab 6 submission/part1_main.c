#include "msp.h"

/**
 * main.c
 */
#define MOTOR_F_HZ 40

void SysTick_Init(void);
void SysTick_delay_ms(uint16_t delay);
void SysTick_delay_microsec(uint16_t delay);


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;        // stop watchdog timer
    // Duty cycle in units of 0.1% (1 thousandths)
    int duty_cycle_thousandths = 200;
    int us_per_cycle = 1000000/MOTOR_F_HZ;
    int us_high = us_per_cycle*duty_cycle_thousandths/1000000;
    int us_low = us_per_cycle - us_high;

    // Configure timer, not needed for this part
    // P2DIR |= BIT4; // P2.4 set TA0.1
    // P2SEL0 |= BIT4;
    // P2SEL1 &= ~BIT4;

    // Configure PWM pin. use P6.0 for PWM
    P6DIR |= BIT0;
    P6SEL0 &= ~BIT0;
    P6SEL1 &= ~BIT0;

    // Configure systick
    SysTick_Init();
    // PWM loop
    while (1) {
        // To dynamically change the duty cycle during a debug
        us_per_cycle = 1000000/MOTOR_F_HZ;
        us_high = us_per_cycle*duty_cycle_thousandths/1000;
        us_low = us_per_cycle - us_high;

        // High
        P6OUT |= BIT0;
        SysTick_delay_microsec(us_high);
        // Low
        P6OUT &= ~BIT0;
        SysTick_delay_microsec(us_low);
    }
}

void SysTick_Init(void) {
    //initialization of systick timer
    SysTick -> CTRL = 0;            // disable SysTick During step
    SysTick -> LOAD = 0x00FFFFFF;   // max reload value
    SysTick -> VAL = 0;             // any write to current clears it
    SysTick -> CTRL = 0x00000005;   // enable systick, 3MHz, No Interrupts
}

#define CYCLES_PER_MS 3000
void SysTick_delay_ms(uint16_t delay) {
    SysTick -> LOAD = ((delay*CYCLES_PER_MS)-1);
    SysTick -> VAL = 0; // any write to CVR clears it
    while ((SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}

#define CYCLES_PER_MICROSEC 3
void SysTick_delay_microsec(uint16_t delay) {
    SysTick -> LOAD = ((delay*CYCLES_PER_MICROSEC)-1);
    SysTick -> VAL = 0; // any write to CVR clears it
    while ((SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}
