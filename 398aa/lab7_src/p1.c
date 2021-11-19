#include "msp.h"


/**
 * main.c
 */
int main(void)
{
    unsigned int result;

    P2 -> SEL0 &= ~7;
    P2 -> SEL1 &= ~7;
    P2 -> DIR |= 7;

    ADC14 -> CTL0 = 0x00000010; 
    ADC14 -> CTL0 |= 0x04080300;
    ADC14 -> CTL1 = 0x00000020; 
    ADC14 -> MCTL[5] = 5;


//    P5 -> DIR |= BIT0;
//    P5 -> DIR |= BIT0;
    P5 -> SEL1 |= BIT0;
    P5 -> SEL0 |= BIT0;

    ADC14 -> CTL1 |= 0x00050000;
    ADC14 -> CTL0 |= 2; 

    unsigned int temp;
    while(1){
        ADC14 -> CTL0 |= 1; 
        while(!ADC14->IFGR0);
        result = ADC14 -> MEM[5];
        printf("%d\n", result);
        temp = result * 100*32 / 4096;
        printf("Milivolts: %d \n", temp);

        P2 -> OUT = result >> 8;



    }
}
