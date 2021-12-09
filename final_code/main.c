#include "main.h"

#include "buttons.h"
#include "ir.h"
#include "keypad.h"
#include "lcd.h"
#include "led.h"
#include "piezzo.h"
#include "screens.h"
#include "seg7.h"
#include "tests.h"
#include "timer32.h"

/**
 * main.c
 */
void main(void)
{
    //WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    init_peripherals();
    // menu_play();
    boot_screen();
    menu_main(); 
    while(1);
}

/*
Initializes all the peripherals
Inputs: None
Outputs: None
Side Effects: Modifies peripherals and associated information
*/
void init_peripherals() {
    init_buttons();
    init_keypad();
    init_led_pins();
    init_piezzo();
    init_segment_leds();
    init_t32();
    LCD_init();
}
