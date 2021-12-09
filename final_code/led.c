#include "led.h"

/*
init_led_pins
Initializes LED pins
Inputs: None
Outputs: None
Side Effects: Changes pins used by LED
*/
void init_led_pins() {
    // Set to GPIO pins
    P2SEL1 &= ~(LED_R | LED_G);
    P2SEL0 &= ~(LED_R | LED_G);
    // Direction: Output
    P2DIR  |=  (LED_R | LED_G);
    // Both LEDs off
    P2OUT  &= ~(LED_R | LED_G);
}

/*
on_r_led
Turns on the red LED
Inputs: None
Outputs: None
Side Effects: Changes P2OUT
*/
void on_r_led() {
    P2OUT |= LED_R; 
}

/*
on_g_led
Turns on the green LED
Inputs: None
Outputs: None
Side Effects: Changes P2OUT
*/
void on_g_led() {
    P2OUT |= LED_G;
}

/*
off_r_led
Turns off the red LED
Inputs: None
Outputs: None
Side Effects: Changes P2OUT
*/
void off_r_led() {
    P2OUT &= ~LED_R;
}

/*
off_g_led
Turns off the green LED
Inputs: None
Outputs: None
Side Effects: Changes P2OUT
*/
void off_g_led() {
    P2OUT &= ~LED_G;
}
