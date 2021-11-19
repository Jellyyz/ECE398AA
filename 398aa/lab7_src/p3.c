#include "msp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    unsigned int result;

        P2 -> SEL0 &= ~7;
        P2 -> SEL1 &= ~7;
        P2 -> DIR |= 7;

        ADC14 -> CTL0 = 0x00000010;
        ADC14 -> CTL0 |= 0x04080300;
        ADC14 -> CTL1 = 0x00000020;
        ADC14 -> MCTL[5] = 5;

        P5 -> SEL1 |= BIT0;
        P5 -> SEL0 |= BIT0;

        ADC14 -> CTL1 |= 0x00050000;
        ADC14 -> CTL0 |= 2;

        unsigned int temp;
        unsigned int celsius;
        unsigned int faren;


    unsigned int i;

    LCD_init_pins();
    LCD_init();

    LCD_command(0x0F); // clear display


    while(1){
                ADC14 -> CTL0 |= 1;
                while(!ADC14->IFGR0);
                result = ADC14 -> MEM[5];
                printf("Raw ADC data: %d\n", result);
                temp = result * 100*32 / 4096;
                printf("Milivolts: %d \n", temp);
                celsius = (temp - 500)/ 10;
                printf("Temperature: %d\n", celsius);
                faren = ((celsius * 9) / 5) + 32;
                printf("Temperature: %d\n", faren);
                char c[300];
                char f[300];

                sprintf(c, "%u", celsius);
                sprintf(f, "%u", faren);

                printf("c = %s\n", c);
                printf("f = %s\n", f);


                P2 -> OUT = result >> 8;
                Systick_ms_delay(500);
                    LCD_command(0x80 | 0x00);    // first line of the screen
                    const char name[] = "Current Temp. is";
                    const char *p;
                    for (p = name; *p != 0; p++)
                    {
                        LCD_data(*p);
                    }

                    LCD_command(0x80 | 0x40);    // second line of the screen

                    char name1[2] = c;
                    char *p2;
                    for (p2 = c; *p2 != 0; p2++)
                    {
                       LCD_data(*p2);
                    }
                    LCD_data(223);
                    LCD_data(67);

                    LCD_command(0x80 | 0x10);    // third line of the screen

                    char name2[2] = f;

                    char *p3;
                    for (p3 = f; *p3 != 0; p3++)
                    {
                       LCD_data(*p3);
                    }
                    LCD_data(223);
                    LCD_data(70);


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

    P6OUT = data|control; // rs=0; rw=0
    Systick_ms_delay(1);
    P6OUT = data|control|EN; //pulse enable signal to write
    Systick_ms_delay(1);
    P6OUT = data|control;
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
    P6SEL0 &= ~0xFF; // Port4.0 clear to 0
    P6SEL1 &= ~0xFF; // Port4.1 clear to 0
    P6DIR = 0xFF;    // sets port 4 as output
    Systick_ms_delay(30);
    P6OUT &= ~0xFF;    // set all of port 4s to 0

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




