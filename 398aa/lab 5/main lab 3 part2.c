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
    unsigned int i;
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    LCD_init_pins();
    LCD_init();

    LCD_command(0x0F); // clear display

    LCD_command(0x80 | 0x00);    // first line of the screen

    const char name[] = "Gally";
    const char *p;
    for (p = name; *p != 0; p++)
    {
        LCD_data(*p);
    }

    LCD_command(0x80 | 0x40);    // second line of the screen

    const char name1[] = "Zhuxuan";
    const char *p2;
    for (p2 = name1; *p2 != 0; p2++)
    {
            LCD_data(*p2);
    }

    LCD_command(0x80 | 0x10);    // second line of the screen

       const char name2[] = "ECE398 AA";
       const char *p3;
       for (p3 = name2; *p3 != 0; p3++)
       {
               LCD_data(*p3);
       }

    //Systick_ms_delay(500);
    P1->DIR |= BIT0;                        // P1.0 set as output
    while(1){
    P1->OUT ^= BIT0;                    // Blink P1.0 LED on for a higher amount of time
    Systick_ms_delay(500);        // Delay
    }
    LCD_command(0x80);      // set cursor to point to line 1 position 1
    Systick_ms_delay(500);
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

    Systick_ms_delay(100);

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




