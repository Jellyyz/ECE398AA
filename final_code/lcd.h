#ifndef LCD_H
#define LCD_H

#include "util.h"

#define LCD_LEN_MAX 16

enum lcd_pin {
    EN = BIT1,
    RS = BIT0,
    DB4 = BIT4,
    DB5 = BIT5,
    DB6 = BIT6,
    DB7 = BIT7,
    LCD_PINS = (BIT0 | BIT1 | BIT4 | BIT5 | BIT6 | BIT7),
};

void LCD_init(void);
void LCD_nibble_write(unsigned char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);

void LCD_clear(void);
// Assumes null-terminated string sent in with appropriate max length
void LCD_show(char* buf, uint32_t line);


#endif /* LCD_H */
