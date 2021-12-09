#include "lcd.h"

uint8_t line_command[4] = {
    (0x80 | 0x00), (0x80 | 0x40), (0x80 | 0x10), (0x80 | 0x50)
};

// Local function interfaces
void LCD_init_pins(void);

/*
LCD_init_pins
Initialize information used by LCD
Inputs: None
Outputs: None
Side Effects: Changes pins used to communicate with LCD
*/
void LCD_init_pins(void) {
    P6SEL0  &= ~LCD_PINS;   // Select GPIO
    P6SEL1  &= ~LCD_PINS;   // Select GPIO
    P6DIR   |= LCD_PINS;    // Set as output
    Systick_ms_delay(30);
    P6OUT   &= ~LCD_PINS;   // Set to 0
}

// Externally visible functions (through header file)
/*
LCD_init
Initializes the LCD with commands
Inputs: None
Outputs: None
Side Effects: Changes the LCD
*/
void LCD_init(void) {
    LCD_init_pins();

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

/*
LCD_nibble_write
Writes data and control information to the LCD
Inputs: Data and control information
Outputs: None
Side Effects: Changes the LCD
*/
void LCD_nibble_write(unsigned char data, unsigned char control) {
    // No need for keeping track of the non LCD pins if they are not used for 
    // anything (comment out)
    // uint8_t same;
    data &= 0xF0; // clear lower nibble for control
    control &= 0x0F; // clear upper nibble for data

    // same = P6OUT & (~LCD_PINS);
    // OR with same if necessary
    P6OUT = data|control; // rs=0; rw=0
    Systick_ms_delay(1);
    P6OUT = data|control|EN; //pulse enable signal to write
    Systick_ms_delay(1);
    P6OUT = data|control;
    Systick_ms_delay(1);
}

/*
LCD_command
Sends a command to the LCD
Inputs: Command information
Outputs: None
Side Effects: Modifies LCD with sent command
*/
void LCD_command(unsigned char command) {
    LCD_nibble_write(command & 0xF0, 0); // upper
    LCD_nibble_write(command << 4, 0);   // lower
    // Why?
    if(command < 4) {
        Systick_ms_delay(4);
    } else {
        Systick_ms_delay(1);
    }
}

/*
LCD_data
Sends data to the LCD
Inputs: Data information
Outputs: None
Side Effects: Modifies LCD with sent data
*/
void LCD_data(unsigned char data) {
    LCD_nibble_write(data & 0xF0, RS);
    LCD_nibble_write(data << 4, RS);
    Systick_ms_delay(1);
}

/*
LCD_clear
Clear LCD screen
Inputs: None
Outputs: None
Side Effects: Modifies LCD screen
*/
void LCD_clear() {
    int i;
    LCD_command(0x0F);
    static char empty_str[] = "                ";
    for (i = 0; i < 4; i++) {
        LCD_show(empty_str, i);
    }
}

/*
LCD_show
Writes a string to the desired line of the LCD
Assumes valid line provided
Inputs: pointer to buffer, desired line
Outputs: None
Side Effects: Modifies LCD screen
*/
void LCD_show(char *buf, uint32_t line) {
    int i;
    LCD_command(line_command[line]);
    for (i = 0; buf[i] != '\0'; i++) {
        LCD_data(buf[i]);
    }
}
