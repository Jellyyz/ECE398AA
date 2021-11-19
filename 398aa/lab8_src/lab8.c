#include "msp.h"

/**
 * main.c
 */
void Systick_ms_delay(uint16_t ms_delay);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;        // stop watchdog timer
    // Duty cycle in units of 0.1% (1 thousandths)

    // Configure timer
    // The config function sets CCR[0] to 32768/10 or 32768/14, then
    // sets CCR[1] to half of that for a duty cycle of 50%
    // The output pin is also configured accordingly.

    // configure ADC
    ADC14 -> CTL0 = 0x00000010;
    ADC14 -> CTL0 |= 0x04080300;
    ADC14 -> CTL1 = 0x00000020;
    ADC14 -> MCTL[5] = 5;

    P5 -> SEL1 |= BIT0;
    P5 -> SEL0 |= BIT0;

    ADC14 -> CTL1 |= 0x00050000;
    ADC14 -> CTL0 |= 2;

    P2->DIR |= BIT0;                        // P2.0 set as output
    P2->DIR |= BIT1;                        // P2.1 set as output
    P2->DIR |= BIT2;                        // P2.2 set as output
    unsigned int i;
    unsigned int result;
    unsigned int temp;
    while(1){
         ADC14 -> CTL0 |= 1;
         while(!ADC14->IFGR0);
         result = ADC14 -> MEM[5];
         printf("Raw ADC data: %d\n", result);
         temp = result * 100*32 / 4096;
         printf("Milivolts: %d \n", temp);

         P2->OUT &= 0x0;                     // Clear all the bits on the register (set them to off)

         if(temp < 1900){
             // yellow for thirty seconds
             P2->OUT ^= BIT0;                    // Set P2.0 LED on
             P2->OUT ^= BIT1;                    // Set P2.1 LED on
            // 30 seconds
            for(i = 0; i < 3 ; i++){
                Systick_ms_delay(1000);
                printf("I: %d \n", i);
                printf("Current State: Yellow.\n");

            }
            while(temp < 1900){
                P2->OUT &= 0x0;                     // Clear all the bits on the register (set them to off)
                P2->OUT ^= BIT1;                    // Set P2.1 LED on
                printf("Current State: Green. \n");
                ADC14 -> CTL0 |= 1;
                while(!ADC14->IFGR0);
                result = ADC14 -> MEM[5];
                printf("Raw ADC data: %d\n", result);
                temp = result * 100*32 / 4096;
                printf("Milivolts: %d \n", temp);

            }
         }


         if(temp > 1900){
         // Blink red if detected that the two leds are close together
             P2->OUT ^= BIT0;                    // Set P2.0 LED on
             printf("Current State: Red. \n");

         }


    }

}

void Systick_ms_delay(uint16_t ms_delay){
    SysTick -> LOAD = ms_delay*3000 -1;
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000005;
    while((SysTick -> CTRL & 0x10000) == 0);
}
