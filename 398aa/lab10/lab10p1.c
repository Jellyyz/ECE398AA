#include "msp.h"

#define USE_SYSTICK_MOTOR 0
#define MOTOR_F 30
#define SYSTICK_F 3000000
// every 0.5ms
#define SYSTICK_CYCLES 1500
#define MOTOR_CYCLES ((SYSTICK_F / SYSTICK_CYCLES) / MOTOR_F)
#define ACLK_F 32768
#define LED_S_INTR_CNT MOTOR_F 
/**
 * main.c
 */
volatile uint32_t timeout_systick = 1;
volatile uint32_t timeout_ta = 1;
// When using systick for both motor and light, the systick runs at a high 
// frequency, following the motor. Counts the number of interrupts, resets
// every 1s.
volatile uint32_t intr_led_count = 0;
// Control the PWM rate
volatile uint32_t intr_motor_count = 0;

// Duty cycle in units of 0.1% (1 thousandths)
uint32_t duty_cycle_thousandths = 180;
uint32_t high_ticks;
uint32_t timerA_ticks = 0; // We will use the timer A iterations to count.

void port1IRQhandler(void);

void SysTick_Init_interrupt(void);
void SysTick_Handler(void);
void TA1_Init(uint32_t duty_cycle_thousandths);
void TA1_0_IRQHandler(void);
void TA1_N_IRQHandler(void);

/* 
Main function 
Inputs: None
Outputs: None
Side Effects: Executes the program
*/
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	// Set the pins as output through the LEDs 
	P2DIR |= BIT0;                        // P2.0 set as output
	P2DIR |= BIT1;                        // P2.1 set as output
    P2DIR |= BIT2;                        // P2.2 set as output
	// Ensure LED starts out as off
	P2OUT &= ~BIT0;
	P2OUT &= ~BIT1;
	P2OUT &= ~BIT2;

	if (!USE_SYSTICK_MOTOR) {
		NVIC_EnableIRQ(TA1_0_IRQn);
		NVIC_EnableIRQ(TA1_N_IRQn);
        if (NVIC_GetEnableIRQ(TA1_0_IRQn)) {
            printf("TA1_0 Int enabled \n");
        }
        if (NVIC_GetEnableIRQ(TA1_N_IRQn)) {
            printf("TA1_N Int enabled \n");
        }
    	// Configure timer
		TA1_Init(duty_cycle_thousandths);
	}

	// Configure PWM pin. use P6.0 for PWM
    P6DIR |= BIT0;
    P6SEL0 &= ~BIT0;
    P6SEL1 &= ~BIT0;
    P6OUT &= ~BIT0;

    // Start timer 
	SysTick_Init_interrupt();
	__enable_irq();
	while(1){
		if (timeout_systick) {
			// LED
			intr_led_count++;
			if (intr_led_count == (SYSTICK_F / 2) / SYSTICK_CYCLES) {
				intr_led_count = 0;
	    		P2OUT ^= BIT0;
			}
			// Motor if systick used to control it
			if (USE_SYSTICK_MOTOR) {
				intr_motor_count++;
            	if (intr_motor_count < (MOTOR_CYCLES * duty_cycle_thousandths) / 1000) {
            	    P6OUT |= BIT0;
            	} else {
            	    P6OUT &= ~BIT0;
            	}
            	if (intr_motor_count == MOTOR_CYCLES) {
            	    intr_motor_count = 0;
            	}
			}
            timeout_systick = 0;
		}
	}
}

/* 
Initializes the systick registers 
Inputs: None
Outputs: None
Side Effects: Changes Systick control registers*/
void SysTick_Init_interrupt(void) {
    SysTick -> CTRL = 0;            // disable SysTick During step
    SysTick -> LOAD = SYSTICK_CYCLES;      // reload value of 0.5s interrupts
    SysTick -> VAL = 0;             // any write to current clears it
    SysTick -> CTRL = 0x00000007;   // enable systic, 3Mhz, Interrupts
}

/*
Interrupt handler when Systick fires an interrupt.
Inputs: None
Outputs: None
Side Effects: Changes global variable keeping track of a timeout
*/
void SysTick_Handler(void){
    timeout_systick = 1;                    // set flag for timeout of SysTick, rest in main
}

/*
Initializes Timer A1
Inputs: None
Outputs: None
Side Effects: Changes Timer A1's registers
*/
void TA1_Init(uint32_t duty_cycle_thousandths) {
    TA1CCR0 = ACLK_F/MOTOR_F;
    TA1CCR1 = (uint16_t) (((ACLK_F/MOTOR_F)*duty_cycle_thousandths)/1000);
    // Reset-set output mode
    TA1CCTL0 = 0x00F0;
    TA1CCTL1 = 0x00F0; // Interrupt enabled
    TA1CCTL2 = 0x0000;
    TA1CCTL3 = 0x0000;
    TA1CCTL4 = 0x0000;
    // ACLK, Up Mode, Timer A Clear
    // Timer A Interrupt Enable - off
    TA1CTL = 0x0114;
}

/*
Interrupt handler, handles Timer CCTL0 reaching the maximum value
Inputs: None
Outputs: None
Side Effects: Changes P6.0 and the interrupt flag
*/
void TA1_0_IRQHandler (void) {
    TA1CCTL0 &= ~BIT0;
    P6OUT |= BIT0;
}

/*
Interrupt handler, handles Timer CCTL1 reaching the threshold value
Inputs: None
Outputs: None
Side Effects: Changes P6.0 and the interrupt flag
*/
void TA1_N_IRQHandler (void) {
    TA1CCTL1 &= ~BIT0;
    P6OUT &= ~BIT0;
}




