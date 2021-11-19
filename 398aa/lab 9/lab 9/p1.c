#include "msp.h"

void UART0_init(void);
void delayMs(int n);
/**
 * main.c
 */
void main(void)
{
    UART0_init();
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	while(1){

		// tell the user hello 
	    while(!(EUSCI_A0->IFG));
	    while(!(EUSCI_A0->IFG & 0X02)){}
	    EUSCI_A0 -> TXBUF = 'H';
	    while(!(EUSCI_A0->IFG & 0X02)){}
	    EUSCI_A0 -> TXBUF = 'E';
	    while(!(EUSCI_A0->IFG & 0X02)){}
	    EUSCI_A0 -> TXBUF = 'L';
	    while(!(EUSCI_A0->IFG & 0X02)){}
	    EUSCI_A0 -> TXBUF = 'L';
	    while(!(EUSCI_A0->IFG & 0X02)){}
	    EUSCI_A0 -> TXBUF = 'O';
	    while(!(EUSCI_A0->IFG & 0X02)){}
	    EUSCI_A0 -> TXBUF = '\n';
	    delayMs(1500);
	    while(!(EUSCI_A0->IFG & 0X01)){}
	        while(1){
	        if(EUSCI_A0 -> RXBUF == '\n'){
	                   break;
	           }
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
