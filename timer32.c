#include "timer32.h"
#define TICKS_1S    3000000
#define TICKS_30S   (TICKS_1S * 30)
#define SHORT_TIME_MAGIC ((uint32_t) 1)

/*
init_t32
Initializes information for timer32
Inputs: None
Outputs: None
Side Effects: Changes registers and information related to timer32. 
Initializes interrupts
*/
void init_t32() {
    // Clear interrupts (any write will clear it)
    TIMER32_1->INTCLR = 0;
    TIMER32_1->LOAD = SHORT_TIME_MAGIC;
    
    /*
    Reserved: [31:8] = 0
    Timer enabled: bit7 = 1,
    Periodic mode: bit6 = 1,
    Interrupt enabled: bit5 = 1,
    Reserved: bit4 = 0,
    Prescale - divide clock by 1: [3:2] = 00,
    32 bit counter: bit1 = 1,
    One-shot mode: bit0 = 1
    */
    TIMER32_1->CONTROL = 0x000000E3;


    NVIC->ISER[(T32_INT1_IRQn)/32] = 1 << (T32_INT1_IRQn % 32);
    if (NVIC_GetEnableIRQ(T32_INT1_IRQn)) {
        printf("T32 INT1 IRQ enabled \n");
    } else {
        printf("[ERROR]: T32 INT1 IRQ not enabled \n!");
    }
    
    // Let first interrupt fire so that the timer is enabled, then clear 
    // the flag. This allows the timer to be enabled and the flag to be 
    // initialized to clear.
    // Only when interrupts are enabled does the first handler fire.
    t32_int_flag = 0;

}

/*
t32_enable
Enables interrupts on the timer32
Inputs: None
Outputs: None
Side Effects: Changes timer32 registers
*/
void t32_enable() {
    // Bit 7 is timer enable
    TIMER32_1->CONTROL |= 0x080;
}

/*
t32_disable
Disables interrupts on the timer32
Inputs: None
Outputs: None
Side Effects: Chagnes timer32 registers
*/
void t32_disable() {
    // Bit 7 is timer enable
    TIMER32_1->CONTROL &= ~0x080;
}

/*
t32_delay_seconds
Sets the timer32 to fire an interupt after a number of seconds
Inputs: The number of seconds
Outputs: None
Side Effects: Modifies timer32 to fire an interrupt later
*/
void t32_delay_seconds(int n) {
    TIMER32_1->LOAD = (uint32_t) (TICKS_1S * n);
}

/*
t32_delay_30s
Sets timer32 to fire an interrupt 30 seconds later
Inputs: None
Outputs: None
Side Effects: Modifies timer32 to fire an interrupt later
*/
void t32_delay_30s() {
    // Necessary to deal with possibility flag is alr set.
    TIMER32_1->LOAD = (uint32_t) TICKS_30S;
}

/*
T32_INT1_IRQHandler
Interrupt handler for timer32
Inputs: None
Outputs: None
Side Effects: Modifies the flag to keep track of timer32 interrupts
*/
void T32_INT1_IRQHandler() {
    t32_int_flag = 1;
    // Clear T32 interrupts (any write will clear it)
    TIMER32_1->INTCLR = 0;
}
