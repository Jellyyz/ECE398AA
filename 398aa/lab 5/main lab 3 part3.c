#include "msp.h"

/**
 * main.c
 */
#define EN BIT1
#define RS BIT0

void LCD_nibble_write(unsigned char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void LCD_init_pins();
void Systick_ms_delay(uint16_t ms_delay);
void Systick_us_delay(uint16_t ms_delay);


void main(void)
{
    //WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    LCD_init_pins();
    LCD_init();

    LCD_command(0x0F); // clear display

    LCD_command(0x80 | 0x40);    // second line of the screen

    uint8_t t;

    const char value[] = "LABORATORY OVER";

    const char *p2;

    int p, start, i, j;

//    int i = 0;
//    for (p2 = value, i = 0; (*p2 != 0) && (i < 3); p2++, i++){
//        printf("%c", *p2);
//        printf("\r");
//    }


    while(1){
         for (t = 0; t <= 16; t++)
         {
         // move to beginning of 2nd line
         LCD_command(0x80 | 0x40);

         int nc, i = 0;
         // prepad
         for (nc = 0; nc < 16 && nc < t; nc++) // if the number of character is less than 16 and our time step is less than 16 then we will print a space for each one
         {
             LCD_data(' ');

         }

         // string
         for (p2 = value; nc < 16 && *p2 != 0; nc++, p2++)
         {
             LCD_data(*(p2));
         }
         //printf("t = %d\n", t);
         Systick_ms_delay(125);         // delay of 125 ms
         }

        //    p[14]
        //    p[13]p[14]

         LCD_command(0x80 | 0x40);
         //for(t = 0; t <= 15; t++){
            for(i = 0; i < 15; i++){

                 LCD_command(0x80 | 0x40);                                      // move back to beginning every time
                 p2 = value;

                 for(j = 0; j <= i; j++){

                 LCD_data(p2[14 - i + j]);                                 // trying to find the index to print
                 //printf("p2[14 - i] = %c\n", p2[14 - i + j]);

                 }
                 Systick_ms_delay(125);
                }
           //}

    }
    //Systick_ms_delay(500);
    P1->DIR |= BIT0;                        // P1.0 set as output
    while(1){
        P1->OUT ^= BIT0;                    // Blink P1.0 LED on for a higher amount of time
        Systick_ms_delay(500);        // Delay
    }


}
void LCD_nibble_write(unsigned char data, unsigned char control){
    data &= 0xF0; // clear lower nibble for control
    control &= 0x0F; // clear upper nibble for data

    P4OUT = data|control; // rs=0; rw=0
    Systick_ms_delay(1);
    P4OUT = data|control|EN; //pulse enable signal to write
    Systick_ms_delay(1);
    P4OUT = data|control;
    Systick_ms_delay(1);

}

void LCD_command(unsigned char command){
    LCD_nibble_write(command & 0xF0, 0); //upper
    LCD_nibble_write(command << 4, 0);   // lower
    if(command < 4)
        Systick_ms_delay(4);
    else
        Systick_ms_delay(1);

}
void LCD_data(unsigned char data){
    LCD_nibble_write(data & 0xF0, RS);
    LCD_nibble_write(data << 4, RS);
    Systick_ms_delay(1);
}

void LCD_init(void){

    Systick_ms_delay(100);    // this code goes through the init process of the lcd

    LCD_nibble_write(0x30, 0);
    Systick_ms_delay(10);

    LCD_nibble_write(0x30, 0);
    Systick_ms_delay(1);

    LCD_nibble_write(0x30, 0);
    Systick_ms_delay(1);

    LCD_nibble_write(0x20, 0);
    Systick_ms_delay(10);

    LCD_command(0x28);
    Systick_ms_delay(10);

    LCD_command(0x08);
    Systick_ms_delay(10);

    LCD_command(0x01);
    Systick_ms_delay(10);

    LCD_command(0x06);
    Systick_ms_delay(10);

}
void LCD_init_pins(){
    P4SEL0 &= ~0xFF; // Port4.0 clear to 0
    P4SEL1 &= ~0xFF; // Port4.1 clear to 0
    P4DIR = 0xFF;    // sets port 4 as output
    Systick_ms_delay(30);
    P4OUT &= ~0xFF;    // set all of port 4s to 0

}

void Systick_ms_delay(uint16_t ms_delay){
    SysTick -> LOAD = ms_delay*3000 -1;
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000005;
    while((SysTick -> CTRL & 0x10000) == 0);
}

void Systick_us_delay(uint16_t ms_delay){
    SysTick -> LOAD = ms_delay*3 -1;
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000005;
    while((SysTick -> CTRL & 0x10000) == 0);
}




