#include "msp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main.c
 */
#define NUM_COLS 3
#define STAR 10
#define KEYPAD_ZERO 11
#define POUND 12
#define false 0; 
#define true 1; 
#define EN BIT1
#define RS BIT0
#define INVALID_KEYPRESS -1
#define NUM_CHARS_PWM 3
int PWMglobal = 0; 
enum off_on {
    OFF = 0,
    ON = 1,
} off_on;

void ADC_init(void); 
uint32_t getPWM(void);
void LCD_nibble_write(unsigned char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void LCD_init_pins();
void Systick_ms_delay(uint16_t ms_delay);
void Systick_us_delay(uint16_t ms_delay);
int8_t Read_Keypad(void);
int8_t keypresschar(char *char_loc, int8_t num_read);
uint32_t getPIN(char* buf);

// helper functions for each menu 
void Alarm(void);
void Door(void);
void Fan(void);
void Light(void); 
void lights_pwm();
void menu(void);
void PWM(void);

void on_fan(void);
void set_fan(uint32_t duty_cycle);
void off_fan(void);
void open_door(void);
void close_door(void);
void open_door_servo(void);
void close_door_servo(void);
void red_light_blink(void);
void check_buzzer(void); 
void on_buzzer(void);
void off_buzzer(void);
void on_lights(void);
void set_lights(uint32_t brightness);
void off_lights(void);
void init_button_intr(void);
void PORT5_IRQHandler(void);


void test_piezzo(void);
void test_piezzo_ta(void);
void test_servo_0(void);
void test_servo_1(void);
void test_yellow_leds(void);
void test_fan(void);
void test_pins(void);
int fdc = 0; 
int door_status = false; // door is initally closed
int alarm_status = true; // the system initially armed
int lights_status = OFF; // lights initially off
static int lights_ccr = 1500; // Start with ccr for half bright
static int fan_ccr = 0;

volatile int servo_int_flag = 0;  
void menu(void){
    LOOP: do {
        int flag = 0; 
        LCD_command(0x0F); // clear display
        LCD_command(0x80 | 0x00);    // first line of the screen
        const char lights[] = "    Menu:          ";
        const char *pl;
        for (pl = lights; *pl != 0; pl++)
        {
            LCD_data(*pl);
        }

        LCD_command(0x80 | 0x40);    // second line of the screen
        const char secondline[] = "1 Alarm 2 Door          ";
        const char *p2; 
        for (p2 = secondline; *p2 != 0; p2++)
        {
            LCD_data(*p2);
        }

        LCD_command(0x80 | 0x10);    // third line of the screen
        const char thirdline[] = "3 Fan 4 Lights         ";
        const char *p3;
        for (p3 = thirdline; *p3 != 0; p3++)
        {
            LCD_data(*p3);
        }
        while(1){
            int8_t key_press = Read_Keypad();
            // printf("Key Pressed: %d\n", key_press);
                if(key_press != INVALID_KEYPRESS) {
                    switch(key_press){
                        case 1:
                            Alarm();
                            flag = 1; 
                            break;
                        case 2:
                            Door();
                            flag = 1; 
                            break; 
                        case 3:
                            Fan();
                            flag = 1; 
                            break; 
                        case 4:
                            Light();
                            flag = 1;
                            break;
                        default: 
                            printf("Press a valid number.\n");
                    }
                }
            if(flag){
                goto LOOP; 
            } 
            LCD_command(0x80 | 0x50);    // fourth line of the screen
            const char fourthline[] = "Temp is: ";
            const char *p40;
            for (p40 = fourthline; *p40 != 0; p40++)
            {
                LCD_data(*p40);
            }
            int result; 
            int temp; 
            int celsius; 
            int faren; 
            ADC14 -> CTL0 |= 1;
            while(!ADC14->IFGR0);
            result = ADC14 -> MEM[5];
            //printf("Raw ADC data: %d\n", result);
            temp = result * 100*32 / 4096;
            //printf("Milivolts: %d \n", temp);
            celsius = (temp - 500)/ 10;
            //printf("Temperature: %d\n", celsius);
            faren = ((celsius * 9) / 5) + 32;
            //printf("Temperature: %d\n", faren);
            char c[300];
            char f[300];

            sprintf(c, "%u", celsius);
            sprintf(f, "%u", faren);

            //printf("c = %s\n", c);
            //printf("f = %s\n", f);

            // char name2[2] = f;
            char *p4;
            for (p4 = f; *p4 != 0; p4++)
            {
                LCD_data(*p4);
            }
            LCD_data(223);
            LCD_data(70);

        }
    } while(1);
}
void Alarm(void){
    LCD_command(0x0F); // clear display
    LCD_command(0x80 | 0x00);    // first line of the screen
    const char lights[] = "    Alarm:          ";
    const char *pl;
    for (pl = lights; *pl != 0; pl++)
    {
        LCD_data(*pl);
    }

    LCD_command(0x80 | 0x40);    // second line of the screen
    const char secondline[] = "1 Armed          ";
    const char *p2; 
    for (p2 = secondline; *p2 != 0; p2++)
    {
        LCD_data(*p2);
    }

    LCD_command(0x80 | 0x10);    // third line of the screen
    const char thirdline[] = "2 Disarmed         ";
    const char *p3;
    for (p3 = thirdline; *p3 != 0; p3++)
    {
        LCD_data(*p3);
    }

    LCD_command(0x80 | 0x50);    // third line of the screen
    const char fourthline[] = "9 Main Menu       ";
    const char *p40;
    for (p40 = fourthline; *p40 != 0; p40++)
    {
        LCD_data(*p40);
    }
    while(1){
    int8_t key_press = Read_Keypad();
        // printf("Key Pressed: %d\n", key_press);
        if(key_press != -1){
            switch(key_press){
            case 1:
            // arm the alarm 
            alarm_status = true; 
            // check if the buzzer should be sounded 
            check_buzzer(); 
                break;
            case 2:
            // disarm the alarm
            alarm_status = false;
            // check if the buzzer should be sounded 
            check_buzzer(); 
                break; 
            case 9:
                return; 
            }
        }
    }
    
}
void Door(void){
    LCD_command(0x0F); // clear display
    LCD_command(0x80 | 0x00);    // first line of the screen
    const char lights[] = "    Door:          ";
    const char *pl;
    for (pl = lights; *pl != 0; pl++)
    {
        LCD_data(*pl);
    }

    LCD_command(0x80 | 0x40);    // second line of the screen
    const char secondline[] = "1 Open  2 Closed";
    const char *p2; 
    for (p2 = secondline; *p2 != 0; p2++)
    {
        LCD_data(*p2);
    }

    LCD_command(0x80 | 0x10);    // third line of the screen
    const char thirdline[] = "                   ";
    const char *p3;
    for (p3 = thirdline; *p3 != 0; p3++)
    {
        LCD_data(*p3);
    }

    LCD_command(0x80 | 0x50);    // third line of the screen
    const char fourthline[] = "9 Main Menu       ";
    const char *p40;
    for (p40 = fourthline; *p40 != 0; p40++)
    {
        LCD_data(*p40);
    }
    while(1){
    int8_t key_press = Read_Keypad();
        // printf("Key Pressed: %d\n", key_press);
        if(key_press != -1){
            switch(key_press){
            case 1: // open
                open_door(); 
                // check if the buzzer should sound
                check_buzzer(); 
                break;
            case 2: // close
                close_door(); 
                // check if the buzzer should sound 
                check_buzzer(); 
                break;
            case 9:
                return; 
            }
        }
    }
 
}
void Fan(void){   // door should always be initially closed
    door_status = 0;
    while(1){
        LCD_command(0x0F); // clear display
        LCD_command(0x80 | 0x00);    // first line of the screen
        const char lights[] = "(0-100) Speed    ";
        const char *pl;
        for (pl = lights; *pl != 0; pl++)
        {
            LCD_data(*pl);
        }

        LCD_command(0x80 | 0x40);    // second line of the screen
        const char secondline[] = "Finish w/ #      ";
        const char *p2; 
        for (p2 = secondline; *p2 != 0; p2++)
        {
            LCD_data(*p2);
        }

        LCD_command(0x80 | 0x10);    // third line of the screen
        const char clear[] = "                        ";
        const char *c;
        for (c = clear; *c != 0; c++)
        {
            LCD_data(*c);
        }

        LCD_command(0x80 | 0x10);    // third line of the screen
        const char thirdline[] = "Speed: ";
        const char *p3;
        for (p3 = thirdline; *p3 != 0; p3++)
        {
            LCD_data(*p3);
        } 
        char f[300];

        sprintf(f, "%u", fdc);

        //printf("c = %s\n", c);
        //printf("f = %s\n", f);

        // char name2[2] = f;
        char *p4;
        for (p4 = f; *p4 != 0; p4++)
        {
            LCD_data(*p4);
        }
        LCD_command(0x80 | 0x50);    // third line of the screen
        const char fourthline[] = "Only # for main menu";
        const char *p40;
        for (p40 = fourthline; *p40 != 0; p40++)
        {
            LCD_data(*p40);
        }

        uint32_t key_press = getPWM();
        // printf("Key Pressed: %d\n", key_press);
        set_fan(key_press);
        on_fan();
        return;
    }
 
}
void Light(void){
    LOOP:do{
        while(1){
        int flag = 0; 
        LCD_command(0x0F); // clear display
        LCD_command(0x80 | 0x00);    // first line of the screen
        const char lights[] = " House Lights:";
        const char *pl;
        for (pl = lights; *pl != 0; pl++)
        {
            LCD_data(*pl);
        }

        LCD_command(0x80 | 0x40);    // second line of the screen
        const char secondline[] = "1 ON 2 OFF           ";
        const char *p2;
        for (p2 = secondline; *p2 != 0; p2++)
        {
            LCD_data(*p2);
        }
        LCD_command(0x80 | 0x10);    // third line of the screen
        const char clear[] = "                              ";
        const char *c;
        for (c = clear; *c != 0; c++)
        {
            LCD_data(*c);
        }
        LCD_command(0x80 | 0x10);    // third line of the screen
        const char thirdline[] = "4 PWM: ";
        const char *p3;
        for (p3 = thirdline; *p3 != 0; p3++)
        {
            LCD_data(*p3);
        }
        int pwm;

        pwm = PWMglobal; 
        char f[300];

        sprintf(f, "%u", pwm);

        //printf("c = %s\n", c);
        //printf("f = %s\n", f);

        // char name2[2] = f;
        char *p4;
        for (p4 = f; *p4 != 0; p4++)
        {
            LCD_data(*p4);
        }

        LCD_command(0x80 | 0x50);    // third line of the screen
        const char fourthline[] = "9 Main Menu          ";
        const char *p40;
        for (p40 = fourthline; *p40 != 0; p40++)
        {
            LCD_data(*p40);
        }
        int8_t key_press = Read_Keypad();
        // printf("Key Pressed: %d\n", key_press);
        if(key_press != -1){
            switch(key_press){
            case 1: 
                on_lights();
                flag = 1; 
                break;
            case 2:
                off_lights();
                flag = 1; 
                break; 
            case 4:
                lights_pwm();
                flag = 1; 
                break; 
            case 9:
                return; 
            }
        }


    }  

}while(1);    
}
void lights_pwm(){
    
    while(1){
        LCD_command(0x0F); // clear display
        
        
        LCD_command(0x80 | 0x00);    // first line of the screen
        const char lights[] = "Light PWM:            : ";
        const char *pl;
        for (pl = lights; *pl != 0; pl++)
        {
            LCD_data(*pl);
        }

        LCD_command(0x80 | 0x40);    // second line of the screen
        const char secondline[] = "Enter the PWM:        ";
        const char *p2;
        for (p2 = secondline; *p2 != 0; p2++)
        {
            LCD_data(*p2);
        }
        LCD_command(0x80 | 0x10);    // third line of the screen
        const char clear[] = "                        ";
        const char *c;
        for (c = clear; *c != 0; c++)
        {
            LCD_data(*c);
        }
        LCD_command(0x80 | 0x50);    // fourth line of the screen
        const char fourthline[] = "WILL AUTO EXIT";
        const char *p40;
        for (p40 = fourthline; *p40 != 0; p40++)
        {
            LCD_data(*p40);
        }
        uint32_t key_press = getPWM();
        // printf("Key Pressed: %d\n", key_press);
        set_lights(key_press);
        PWMglobal = key_press; 
        return; 
    }
}
void main(void)
{
    // init keypad
    P4SEL0 = 0x00;
    P4SEL1 = 0x00;
    P4DIR = 0x00; // Set cols to high Z (input) and rows to input
    P4REN = 0x0F; // Enable row pull resistors
    P4OUT = 0x0F; // Configure and use the pull resistors
    
    // init yellow LEDS
    // Select TimerA_0.2, 0.3, 0.4
    P2SEL0 |= (BIT5 | BIT6 | BIT7);
    P2SEL1 &= ~(BIT5 | BIT6 | BIT7);

    // Direction: Output
    P2DIR |= (BIT5 | BIT6 | BIT7);
    TA0CCR0 = 3000;
    TA0CCR2 = 3000;
    TA0CCR3 = 3000;
    TA0CCR4 = 3000;
    TA0CCTL0 = 0;
    TA0CCTL2 = 0x00E0;
    TA0CCTL3 = 0x00E0;
    TA0CCTL4 = 0x00E0;
    lights_status = OFF;

    // Init fan
    // P7.7
    P7SEL0 |= BIT7;
    P7SEL1 &= ~BIT7;
    P7DIR |= BIT7;
    // TimerA_1.1
    TA1CCR0 = 820;
    TA1CCR1 = 0;
    TA1CCTL0 = 0;
    TA1CCTL1 = 0x00E0;
    
    // init door LEDs
    P1SEL0 &= ~(BIT6 | BIT7);
    P1SEL1 &= ~(BIT6 | BIT7);
    P1OUT &= ~(BIT6 | BIT7);
    P1DIR |= (BIT6 | BIT7);

    // Init door motor
    // Select TimerA_3.2
    P8SEL0 |= BIT2;
    P8SEL1 &= ~BIT2;
    // Direction: Output
    P8DIR |= BIT2;
    // TA3CCTL0
    TA3CCR0 = 60000;
    TA3CCR2 = 0;
    TA3CCTL0 = 0x0;
    TA3CCTL2 = 0x00E0;
    close_door();
    // TA3CCTL2
    // Start timer A_3
    // Outmode: Reset-set
    // SMCLK (3MHz), Up mode, clear
    // No interrupts
    // (0x0200) | (0x0010) | (0x0004);
    TA3CTL = 0x0214;

    // Init buzzer
    // Select GPIO
    P5SEL0 |= BIT6;
    P5SEL1 &= ~BIT6;
    // Direction: Output
    P5DIR |= BIT6;

    TA2CCR0 = 750;
    TA2CCR1 = 375;
    TA2CCTL0 = 0x0;
    TA2CCTL1 = 0x00E0;

    // init ADC#define NUM_CHARS_PWM 3

    //test_pins();
    ADC_init();
    LCD_init_pins();
    LCD_init();
    init_button_intr();
    __enable_irq();
    menu();
    // test_piezzo();
    // test_piezzo_ta();
    // test_servo_0();
    // test_servo_1();
    // test_yellow_leds();
    // test_fan();
//     test_pins();
}

/*
Get input from keypad to control PWM cycles.
Inputs: None
Return: Integer corresponding to the duty cycle with a granularity of 0.1%
*/
void ADC_init(){
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
}

uint32_t getPWM() {

    int8_t keypad_val;
    uint32_t elems_keyed_in = 0;
    uint32_t buf[NUM_CHARS_PWM];
    uint32_t i;

    for (i = 0; i < NUM_CHARS_PWM; i++) {
        buf[i] = 0;
    }
    printf("[DEBUG] Getting PWM \n");
    while (1) {
        keypad_val = Read_Keypad();
        // printf("[DEBUG] val %d from keypad!", keypad_val);
        if (keypad_val == POUND) {
            // Done
            break;
        }
        // Valid keypad input
        if (keypad_val != INVALID_KEYPRESS
            && keypad_val != STAR
            && keypad_val != POUND) {
            printf("[DEBUG] keypad_val: %d \n", keypad_val);
            buf[elems_keyed_in] = (keypad_val == KEYPAD_ZERO) ? 0 : keypad_val;
            if (elems_keyed_in == NUM_CHARS_PWM) {
                break;
            } else {
                elems_keyed_in++;
                printf ("Char %d taken in! \n", elems_keyed_in);
            }
        }
    }
    // The elements will be keyed in from the element before null terminate to 0.
    uint32_t out_val = 0;
    for (i = 0; i < elems_keyed_in; i++) {
        out_val *= 10;
        out_val += buf[i];
    }
    if (out_val > 100) {
        printf("Invalid duty cycle of %d! Saturating the value to 100 \n", out_val);
        out_val = 100;
    } else {
        printf("Duty cycle of %d%%! \n", out_val);
    }
    return out_val;
}
void LCD_nibble_write(unsigned char data, unsigned char control){
    data &= 0xF0; // clear lower nibble for control
    control &= 0x0F; // clear upper nibble for data

    P9OUT = data|control; // rs=0; rw=0
    Systick_ms_delay(1);
    P9OUT = data|control|EN; //pulse enable signal to write
    Systick_ms_delay(1);
    P9OUT = data|control;
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
// Pins 6.0, 6.4, 6.5, 6.6, 6.7
// Pin 5.4
void LCD_init_pins(){
    P9SEL0 &= ~0xFF; // Port4.0 clear to 0
    P9SEL1 &= ~0xFF; // Port4.1 clear to 0
    P9DIR = 0xFF;    // sets port 4 as output
    Systick_ms_delay(30);
    P9OUT &= ~0xFF;    // set all of port 4s to 0


}

void Systick_ms_delay(uint16_t ms_delay){
    SysTick -> LOAD = ms_delay*3000 -1;
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000005;
    //while((SysTick -> CTRL & 0x10000) == 0);

}

void Systick_us_delay(uint16_t ms_delay){
    SysTick -> LOAD = ms_delay*3 -1;
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000005;
    while((SysTick -> CTRL & 0x10000) == 0);
}



/*
Reads the keypad
Rows: Ports 4.0, 4.1, 4.2, 4.3
Cols: Ports 4.4, 4.5, 4.6
Return: INVALID_KEYPRESS if nothing pressed
*/
int8_t Read_Keypad(void) {
    volatile uint8_t col;
    volatile uint8_t row;
    volatile int never_pressed = 1; // 0 if pressed, 1 if never pressed at all
    int8_t num_read;

    // Loop through the columns
    for (col = 0; col < NUM_COLS; col++) {
        P4->DIR = 0x00; // Set cols to high Z, Set rows as inputs
        P4->DIR |= (BIT4 << col);   // Set column to output
        P4->OUT &= ~(BIT4 << col);  // Set column to LOW
        // Check for press
        Systick_ms_delay(2000); // Give some delay before reading
        row = P4->IN & 0x0F;
        // Wait for bouncing
        // Systick_ms_delay(10);
        // Check if still pressed
        if ((P4->IN & 0x0F) != 0x0F) {
            never_pressed = 0;
            // Wait for release
            while ((P4->IN & 0x0F) != 0x0F);
            break;
        } else {
            continue;
        }
    }
    // Reset to high Z
    P4->DIR = 0x00;
    // Keypad not pressed
    if (never_pressed) {
        return INVALID_KEYPRESS;
    }
    // Wait for debounce
    Systick_ms_delay(10);
    // printf("Row: %x \n", row);
    // Check if still released not performed to prevent deadlock.
    switch (row) {
        case 0x0E: num_read =     col + 1; break;
        case 0x0D: num_read = 3 + col + 1; break;
        case 0x0B: num_read = 6 + col + 1; break;
        case 0x07: num_read = 9 + col + 1; break;
    }
    return num_read;
}
#undef NUM_COLS

/*
Input: Location to put the char
Return: INVALID_KEYPRESS if nothing pressed
*/
int8_t keypresschar(char *char_loc, int8_t num_read) {
    char outchar; // Char to provide
    // This declaration does not return void.
    switch (num_read) {
        case 1:     outchar = '1'; break;
        case 2:     outchar = '2'; break;
        case 3:     outchar = '3'; break;
        case 4:     outchar = '4'; break;
        case 5:     outchar = '5'; break;
        case 6:     outchar = '6'; break;
        case 7:     outchar = '7'; break;
        case 8:     outchar = '8'; break;
        case 9:     outchar = '9'; break;
        case STAR:  outchar = '*'; break;
        case 11:    outchar = '0'; break;
        case POUND: outchar = '#'; break;
    }
    *char_loc = outchar;
    return 0;
}

uint32_t getPIN(char* buf) {
    int8_t keypad_val;
    uint32_t elems_keyed_in = 0;
    while (1) {
        keypad_val = Read_Keypad();
        if (keypad_val == POUND) {
            // Done
            return elems_keyed_in;
        }
        // Valid keypad input
        if (    keypad_val != INVALID_KEYPRESS
            && keypad_val != STAR
            && keypad_val != POUND) {
            buf[0] = buf[1];
            buf[1] = buf[2];
            buf[2] = buf[3];
            keypresschar(&buf[3], keypad_val);
            if (elems_keyed_in < 4) {
                elems_keyed_in++;
            }
        }
    }
}

void PWM(void){
    return;
}

void on_fan() {
    // Start timer A_1
    // Outmode: Reset-set
    // ACLK (32768Hz), Up mode, clear
    // No interrupts
    // (0x0100) | (0x0010) | (0x0004);
    TA1CTL = 0x0114;
    TA1CCR1 = fan_ccr;
}

void set_fan(uint32_t duty_cycle) {
    uint32_t new_ccr1;
    new_ccr1 = 820 * duty_cycle / 100;
    TA1CCR1 = (uint16_t) new_ccr1;
    fan_ccr = new_ccr1;
    fdc = duty_cycle; 
}

void off_fan() {
    // Start timer A_1
    // Outmode: Reset-set
    // ACLK (32768Hz), Stop mode, clear
    // No interrupts
    // (0x0100) | (0x0000) | (0x0004);
    // TA1CTL = 0x0104;
    TA1CCR1 = 0;
}

void open_door() {
    open_door_servo();
    P1OUT &= ~BIT6;
    P1OUT |= BIT7;
    door_status = true; 
}

void close_door() {
    close_door_servo();
    P1OUT &= ~BIT7;
    P1OUT |= BIT6;
    door_status = false; 
}

void open_door_servo() {
    TA3CCR2 = 1632;
}

void close_door_servo() {
    TA3CCR2 = 4416;
}

void red_led_blink(){
    // red led blinking should be parallel with the buzzer going off 
}

void check_buzzer(){
    if(alarm_status && door_status)
        on_buzzer(); 
    else{
        off_buzzer(); 
    } 
}
void on_buzzer() {
    // Start timer A_2
    // Outmode: Reset-set
    // SMCLK (3MHz), Up mode, clear
    // No interrupts
    // (0x0200) | (0x0010) | (0x0004);
    TA2CTL = 0x0214;
    red_led_blink(); 
}

void off_buzzer() {
    // Start timer A_2
    // Outmode: Reset-set
    // SMCLK (3MHz), Stop mode, clear
    // No interrupts
    // (0x0200) | (0x0000) | (0x0004);
    TA2CTL = 0x0204;
}

void on_lights() {
    // Start timer A_0
    // Outmode: Reset-set
    // SMCLK (3MHz), Up mode, clear
    // No interrupts
    // (0x0200) | (0x0010) | (0x0004);
    TA0CTL = 0x214;
    TA0CCR2 = lights_ccr;
    TA0CCR3 = lights_ccr;
    TA0CCR4 = lights_ccr;
    lights_status = ON;
}

void set_lights(uint32_t brightness) {
    uint32_t new_ccr;
    new_ccr = 3000 * brightness/100;
    TA0CCR2 = (uint16_t) new_ccr;
    TA0CCR3 = (uint16_t) new_ccr;
    TA0CCR4 = (uint16_t) new_ccr;
    lights_ccr = new_ccr;
}

void off_lights() {
    // Start timer A_0
    // Outmode: Reset-set
    // SMCLK (3MHz), Stop mode, clear
    // No interrupts
    // (0x0200) | (0x0000) | (0x0004);
    TA0CCR2 = 0;
    TA0CCR3 = 0;
    TA0CCR4 = 0;
    // TA0CTL = 0x204;
    lights_status = OFF;
}

void toggle_lights() {
    (lights_status == ON) ? off_lights() : on_lights();
}

// Pins 5.4 and 5.5
void init_button_intr() {
    // GPIO
    P5SEL0  &=~ (BIT4 | BIT5);
    P5SEL1  &=~ (BIT4 | BIT5);
    // Input
    P5DIR   &=~ (BIT4 | BIT5);
    P5REN   |= (BIT4 | BIT5);           // enable internal resistor
    P5OUT   |= (BIT4 | BIT5);           // enable pull-up resistor (P1.1 output high)
    P5IES   |= (BIT4 | BIT5);           // set pin interrupt to trigger when it goes from high to low
    P5IE    |= (BIT4 | BIT5);           // enable interrupt for P1.1
    P5IFG   = 0;                        // Clear all P1 interrupt flags

    NVIC->ISER[(PORT5_IRQn)/32] = 1 << (PORT5_IRQn % 32);
    if (NVIC_GetEnableIRQ(PORT5_IRQn)) {
        printf("PORT5 IRQ enabled \n");
    } else {
        printf("[ERROR]: PORT5 IRQ not enabled \n!");
    }
}

// Button interrupt handler
void PORT5_IRQHandler() {
    // P5.4 for lights, P5.5 for fan emergency button
    if (P5IFG & BIT4) {
        toggle_lights();
        P5IFG &= ~BIT4;
    } else if (P5IFG & BIT5) {
        off_fan();
        P5IFG &= ~BIT5;
    }
}

// Assume P3.7, P3.6 is burnt out
// Assume 5.7
void test_piezzo() {
    volatile int i;
    // Select GPIO
    P5SEL0 &= ~BIT6;
    P5SEL1 &= ~BIT6;

    // Direction: Output
    P5DIR |= BIT6;

    while(1) {
        for (i = 0; i < 25; i++) {
            Systick_ms_delay(1);
        }
        P5OUT ^= BIT6;
    }
}

void test_piezzo_ta() {
    volatile int i;
    // Select GPIO
    P5SEL0 |= BIT6;
    P5SEL1 &= ~BIT6;
    // Direction: Output
    P5DIR |= BIT6;

    TA2CCR0 = 750;
    TA2CCR1 = 375;
    TA2CCTL0 = 0x0;
    TA2CCTL1 = 0x00E0;
    // Start timer A_2
    // Outmode: Reset-set
    // SMCLK (3MHz), Up mode, clear
    // No interrupts
    // (0x0200) | (0x0010) | (0x0004);
    TA2CTL = 0x0214;
    while(1);
}

// Assume 8.2
void test_servo_0() {
    volatile int i;
    enum state {
        CLOSED = 0,
        OPEN = 1,
    } ;
    // Select GPIO
    P8SEL0 &= ~BIT2;
    P8SEL1 &= ~BIT2;
    // Select direction
    P8DIR |= BIT2;

    // Direction: Output
    while (1) {
        i = 0;
        while (i < 20) {
            P8OUT |= BIT2;
            Systick_us_delay(544);
            P8OUT &= ~BIT2;
            Systick_us_delay(19456);
            i++;
        }
        for (i = 0; i < 100; i++) {
            Systick_us_delay(10000);
        }
        i = 0;
        while (i < 20) {
            P8OUT |= BIT2;
            Systick_us_delay(1472);
            P8OUT &= ~BIT2;
            Systick_us_delay(18528);
            i++;
        }
        for (i = 0; i < 100; i++) {
            Systick_us_delay(10000);
        }
    }

    // while(1) {
    //     if (servo_int_flag == 1) {
    //         switch (door_state) {
    //             case CLOSED:
                    
    //                 break;

    //             case OPEN:

    //                 break;

    //             default:
    //                 break;
    //         }
    //         servo_int_flag = 0;
    //     }
    // }
}

void test_servo_1() {
    volatile int i;
    // Select TimerA_3.2
    P8SEL0 |= BIT2;
    P8SEL1 &= ~BIT2;

    // Direction: Output
    P8DIR |= BIT2;

    // TA3CCTL0
    TA3CCR0 = 60000;
    TA3CCR2 = 0;
    TA3CCTL0 = 0x0;
    TA3CCTL2 = 0x00E0;
    // TA3CCTL2

    // Start timer A_3
    // Outmode: Reset-set
    // SMCLK (3MHz), Up mode, clear
    // No interrupts
    // (0x0200) | (0x0010) | (0x0004);
    TA3CTL = 0x0214;
    while (1) {
        TA3CCR2 = 1632;
        // TA3CCR2 = 100;
        for (i = 0; i < 100; i++) {
            Systick_us_delay(10000);
        }
        TA3CCR2 = 4416;
        // TA3CCR2 = 400;
        for (i = 0; i < 100; i++) {
            Systick_us_delay(10000);
        }
    }

}

void test_yellow_leds() {
    volatile int i;
    // Select TimerA_0.2, 0.3, 0.4
    P2SEL0 |= (BIT5 | BIT6 | BIT7);
    P2SEL1 &= ~(BIT5 | BIT6 | BIT7);

    // Direction: Output
    P2DIR |= (BIT5 | BIT6 | BIT7);

    // TA3CCTL0
    TA0CCR0 = 3000;
    TA0CCR2 = 0;
    TA0CCR3 = 0;
    TA0CCR4 = 0;
    TA0CCTL0 = 0;
    TA0CCTL2 = 0x00E0;
    TA0CCTL3 = 0x00E0;
    TA0CCTL4 = 0x00E0;
    // Start timer A_0
    // Outmode: Reset-set
    // SMCLK (3MHz), Up mode, clear
    // No interrupts
    // (0x0200) | (0x0010) | (0x0004);
    TA0CTL = 0x0214;
    while (1) {
        TA0CCR2 = 300;
        TA0CCR3 = 300;
        TA0CCR4 = 300;
        for (i = 0; i < 100; i++) {
            Systick_us_delay(10000);
        }
        TA0CCR2 = 600;
        TA0CCR3 = 600;
        TA0CCR4 = 600;
        for (i = 0; i < 100; i++) {
            Systick_us_delay(10000);
        }
        TA0CCR2 = 1800;
        TA0CCR3 = 1800;
        TA0CCR4 = 1800;
        for (i = 0; i < 100; i++) {    // Start timer A_1
    // Outmode: Reset-set
    // ACLK (32768Hz), Up mode, clear
    // No interrupts
    // (0x0100) | (0x0010) | (0x0004);
    TA1CTL = 0x0114;

        }
    }

}

void test_fan() {
    volatile int i;
    // P7.7
    P7SEL0 |= BIT7;
    P7SEL1 &= ~BIT7;

    P7DIR |= BIT7;

    // TimerA_1.1
    TA1CCR0 = 820;
    TA1CCR1 = 0;
    TA1CCTL0 = 0;
    TA1CCTL1 = 0x00E0;
    // Start timer A_1
    // Outmode: Reset-set
    // ACLK (32768Hz), Up mode, clear
    // No interrupts
    // (0x0100) | (0x0010) | (0x0004);
    TA1CTL = 0x0114;
    while(1) {
        TA1CCR1 = 164;
        for (i = 0; i < 100; i++) {
            Systick_us_delay(10000);
        }
        TA1CCR1 = 123;
        for (i = 0; i < 100; i++) {
            Systick_us_delay(10000);
        }
    }
}

void test_pins() {
    P1DIR = 0xFF;
    P1SEL0 = 0;
    P1SEL1 = 0;
    P1OUT = 0xFF;
    P2DIR = 0xFF;
    P2SEL0 = 0;
    P2SEL1 = 0;
    P2OUT = 0xFF;
    P3DIR = 0xFF;
    P3SEL0 = 0;
    P3SEL1 = 0;
    P3OUT = 0xFF;
    P4DIR = 0xFF;
    P4SEL0 = 0;
    P4SEL1 = 0;
    P4OUT = 0xFF;
    P5DIR = 0xFF;
    P5SEL0 = 0;
    P5SEL1 = 0;
    P5OUT = 0xFF;
    P6DIR = 0xFF;
    P6SEL0 = 0;
    P6SEL1 = 0;
    P6OUT = 0xFF;
    P7DIR = 0xFF;
    P7SEL0 = 0;
    P7SEL1 = 0;
    P7OUT = 0xFF;
    P8DIR = 0xFF;
    P8SEL0 = 0;
    P8SEL1 = 0;
    P8OUT = 0xFF;
    P9DIR = 0xFF;
    P9SEL0 = 0;
    P9SEL1 = 0;
    P9OUT = 0xFF;
    P10DIR = 0xFF;
    P10SEL0 = 0;
    P10SEL1 = 0;
    P10OUT = 0xFF;
    while(1);
}


