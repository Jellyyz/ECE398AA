#include "msp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void UART0_init(void);
void delayMs(int n);
/**
 * main.c
 */
void main(void)
{
    UART0_init();
    int i;
    char *ptr;
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    P2->DIR |= BIT0;                        // P2.0 set as output
    P2->DIR |= BIT1;                        // P2.1 set as output
    P2->DIR |= BIT2;                        // P2.2 set as output
    P2OUT &= 0;
    char color[30];
    char freq[30];
    int f_hz;
    volatile uint32_t timer = 40000; // Control the time taken to blink

    while(1){
        // ask the user for input
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = '\n';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'E';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'n';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 't';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'e';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'r';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = ' ';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'a';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = ' ';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'c';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'o';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'l';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'o';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'r';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = '.';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = '\n';
        while(!(EUSCI_A0->IFG & 0X01)){}
        
        memset(color, 0, 30);
        if(EUSCI_A0 -> RXBUF == 'R'){
            strcpy(color, "R");
        }
        else if(EUSCI_A0 -> RXBUF == 'G'){
            strcpy(color, "G");
        }
        else if(EUSCI_A0 -> RXBUF == 'B'){
            strcpy(color, "B");
        }
        
        printf("You entered this color: %s\n", color);
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = '\n';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'E';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'n';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 't';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'e';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'r';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = ' ';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'a';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = ' ';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'f';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'r';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'e';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = 'q';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = '.';
        while(!(EUSCI_A0->IFG & 0X02)){}
        EUSCI_A0 -> TXBUF = '\n'; 

        i = 0;
        while (1) {
            // Wait for bit to turn 1
            while (!(UCA0IFG & 0x01));
            freq[i] = EUSCI_A0 -> RXBUF; // parse in each character
            if(freq[i] == '\n'){         // if we enter a new line then it will blink the led
                i = 0;
                break;
            }
            i++;
        }
        f_hz = strtol(freq, &ptr, 10);   // change the string to long int
        #define SMCLK_F_HZ 1000000
        timer = SMCLK_F_HZ / f_hz;
        #undef SMCLK_F_HZ
        printf("You entered this frequency: %s\n", freq);
        memset(freq, 0, 30);
        printf("Timer cycles: %d \n", timer);
        printf("Color detected: %s \n", color);

        while(strcmp(color, "R") == 0){
            // printf("Red detected \n");
            if(((UCA0IFG & 0x01) != 0) && (EUSCI_A0 -> RXBUF == '\n')){
                break;
            }
            P2->OUT &= 0x0;                     // Clear all the bits on the register (set them to off)
            for (i = 0; i < timer/2; i++);        // Delay
            P2->OUT ^= BIT0;                    // Set P2.0 LED on
            for (i = 0; i < timer/2; i++);        // Delay
        }
        while(strcmp(color, "G") == 0){
            // printf("Green detected \n");
            if(((UCA0IFG & 0x01) != 0) && (EUSCI_A0 -> RXBUF == '\n')){
                break;
            }
            P2->OUT &= 0x00;
            for (i = 0; i < timer/2; i++);        // Delay
            P2->OUT ^= BIT1;
            for (i = 0; i < timer/2; i++);        // Delay
        }
        while(strcmp(color, "B") == 0){
            // printf("Blue detected \n");
            if(((UCA0IFG & 0x01) != 0) && (EUSCI_A0 -> RXBUF == '\n')){
                break;
            }
            P2->OUT &= 0x00;
            for (i = 0; i < timer/2; i++);        // Delay
            P2->OUT ^= BIT2;
            for (i = 0; i < timer/2; i++);        // Delay
        }
    }

}
void UART0_init(void){
        EUSCI_A0->CTLW0 |= 1; // put in reset mode for config
        EUSCI_A0->MCTLW = 0;  // disable oversampling
        EUSCI_A0->CTLW0 = 0x0081; // 1 stop bit, no parity
        EUSCI_A0->BRW = 312; // 3mhz/9600
        P1->SEL0 |= 0x0C; // p1.3 1.2 for uart
        P1->SEL1 &= ~0x0C;
        EUSCI_A0->CTLW0 &= ~1; // take uart out of the reset mode
}
void delayMs(int n){
        int i, j; // delay
        for(j = 0; j < n; j++);
            for(i = 750; i > 0; i--);
}
