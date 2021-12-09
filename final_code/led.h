#ifndef LED_H
#define LED_H

#include "util.h"

enum led_pin {
    LED_R = BIT0,
    LED_G = BIT1,
};

void init_led_pins(void);
void on_r_led(void);
void on_g_led(void);
void off_r_led(void);
void off_g_led(void);

#endif /* LED_H */
