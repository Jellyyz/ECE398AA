#include "msp.h"

/**
 * main.c
 */
#define MOTOR_F 40
#define SMCLK_F 3000000
#define TA_GRANULARITY_HZ 10000 // Count 0.1ms cycles (10KHz)
// How many system cycles per timerA cycle
#define TA_GRANULARITY_CYCLES ((uint16_t) (SMCLK_F/TA_GRANULARITY_HZ))
// How many timerA ticks per motor cycle
#define MOTOR_TA_TICKS (TA_GRANULARITY_HZ / MOTOR_F)

void initkeypad(void);
void pwmloop(uint32_t duty_cycle_thousandths);
void pwmloop_keypad_poll(uint32_t *buf, uint32_t *keys_entered, uint32_t *duty_cycle_thousandths);
void configtimerA0();
void configpwmpin();
void starttimerA0();

void SysTick_Init(void);
void SysTick_delay_ms(uint16_t delay);
void SysTick_delay_microsec(uint16_t delay);

int8_t Read_Keypad(void);
int8_t keypresschar(char *char_loc, int8_t num_read);
uint32_t getPWM(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;        // stop watchdog timer
    // Duty cycle in units of 0.1% (1 thousandths)

    SysTick_Init();
    initkeypad();
    printf("Input duty cycle %%! (Use # to terminate) \n");
    uint32_t duty_cycle_thousandths = getPWM();
    

    // Configure timer
    configtimerA0();

    // Configure PWM pin. use P6.0 for PWM
    configpwmpin();

    // Start timer
    starttimerA0();

    // PWM loop - This is infinite
    pwmloop(duty_cycle_thousandths);
}
/*
Initializes the pin used in the keypad (Pin 4)
Inputs: None
Returns: None
*/
void initkeypad() {
    P4SEL0 = 0x00;
    P4SEL1 = 0x00;
    P4DIR = 0x00; // Set cols to high Z (input) and rows to inputs
    P4REN = 0x0F; // Enable row pull resistors
    P4OUT = 0x0F; // Configure and use the pull resistors
}

/*
Initializes timerA0
Inputs: None
Returns: None
*/
void configtimerA0() {
    P2DIR |= BIT4; // P2.4 set TA0.1
    P2SEL0 |= BIT4;
    P2SEL1 &= ~BIT4;

    TIMER_A0->CCTL[0] = 0x00E0;
    TIMER_A0->CCR[0] = TA_GRANULARITY_CYCLES;
}

/*
Initializes GPIO pin used for outputting PWM
Inputs: None
Returns: None
*/
void configpwmpin() {
    P6DIR |= BIT0;
    P6SEL0 &= ~BIT0;
    P6SEL1 &= ~BIT0;
    P6OUT &= ~BIT0;
}

/*
Starts timerA0 by writing to the CTL register
Inputs: None
Returns: None
*/
void starttimerA0() {
    TIMER_A0->CTL = 0x0214; // SMCLK, Up Mode, clear TAR to start
}

#define NUM_CHARS_PWM 3
/*
Loop to control the motor
Inputs: None
Returns: None
*/
void pwmloop(uint32_t duty_cycle_thousandths) {
    uint32_t timerA_ticks = 0;
    uint32_t keypad_buf[NUM_CHARS_PWM];
    uint32_t i;
    for (i = 0; i < NUM_CHARS_PWM; i++) {
        keypad_buf[i] = 0;
    }
    uint32_t keys_pressed = 0;

    while (1) {
        pwmloop_keypad_poll(keypad_buf, &keys_pressed, &duty_cycle_thousandths);
        uint32_t high_ticks = MOTOR_TA_TICKS * duty_cycle_thousandths/1000;
        while ((TIMER_A0->CCTL[0] & BIT0) != BIT0); // wait until the flag is set
    
        TIMER_A0->CCTL[0] &= ~BIT0;
        // Flag set, increment output.
        timerA_ticks++;

        // Configure pin output
        if (timerA_ticks <= high_ticks) {
            // High
            P6OUT |= BIT0;
        } else {
            // Low
            P6OUT &= ~BIT0;
        }

        // Configure timer to reset every period.
        if (timerA_ticks >= MOTOR_TA_TICKS) {
            timerA_ticks = 0;
        }
    }
}

#define INVALID_KEYPRESS -1
#define NUM_COLS 3

void SysTick_Init(void) {
    //initialization of systick timer
    SysTick -> CTRL = 0;            // disable SysTick During step
    SysTick -> LOAD = 0x00FFFFFF;   // max reload value
    SysTick -> VAL = 0;             // any write to current clears it
    SysTick -> CTRL = 0x00000005;   // enable systick, 3MHz, No Interrupts
}

#define CYCLES_PER_MS 3000
void SysTick_delay_ms(uint16_t delay) {
    SysTick -> LOAD = ((delay*CYCLES_PER_MS)-1);
    SysTick -> VAL = 0; // any write to CVR clears it
    while ((SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}

#define CYCLES_PER_MICROSEC 3
void SysTick_delay_microsec(uint16_t delay) {
    SysTick -> LOAD = ((delay*CYCLES_PER_MICROSEC)-1);
    SysTick -> VAL = 0; // any write to CVR clears it
    while ((SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}

#define STAR 10
#define KEYPAD_ZERO 11
#define POUND 12
/*
Reads the keypad
Rows: Ports 4.0, 4.1, 4.2, 4.3
Cols: Ports 4.4, 4.5, 4.6
Return: INVALID_KEYPRESS if nothing pressed
*/
int8_t Read_Keypad(void) {
    uint8_t col;
    volatile uint8_t row;
    volatile int never_pressed = 1; // 0 if pressed, 1 if never pressed at all
    int8_t num_read;

    // Loop through the columns
    for (col = 0; col < NUM_COLS; col++) {
        P4->DIR = 0x00; // Set cols to high Z, Set rows as inputs
        P4->DIR |= (BIT4 << col);   // Set column to output
        P4->OUT &= ~(BIT4 << col);  // Set column to LOW
        // Check for press
        SysTick_delay_ms(5); // Give some delay before reading
        row = P4->IN & 0x0F;
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
    // SysTick_delay_ms(10);
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
Input: Location to put the char, number representing input from keypad
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

/*
Get input from keypad to control PWM cycles.
Inputs: None
Return: Integer corresponding to the duty cycle with a granularity of 0.1%
*/
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
        out_val = 1000;
    } else {
        printf("Duty cycle of %d%%! \n", out_val);
        out_val *= 10;
    }
    return out_val;
}

void pwmloop_keypad_poll(uint32_t *buf, uint32_t *keys_entered, uint32_t *duty_cycle_thousandths) {
    int8_t keypad_val;
    uint32_t i;
    keypad_val = Read_Keypad();
    // printf("[DEBUG] val %d from keypad!", keypad_val);
    if (keypad_val == INVALID_KEYPRESS) {
        return;
    }
    if (keypad_val == POUND) {
        // Done
        uint32_t out_val = 0;
        for (i = 0; i < *keys_entered; i++) {
            out_val *= 10;
            out_val += buf[i];
        }
        if (out_val > 100) {
            printf("Invalid duty cycle of %d! Saturating the value to 100 \n", out_val);
            out_val = 1000;
        } else {
            printf("Duty cycle of %d%%!, buffer is: %d%d%d \n", out_val, buf[0], buf[1], buf[2]);
            out_val *= 10;
        }
        *duty_cycle_thousandths = out_val;
        *keys_entered = 0;
        for (i = 0; i < NUM_CHARS_PWM; i++) {
            buf[i] = 0;
        }
        return;
    }
    // Valid keypad input
    if (keypad_val != INVALID_KEYPRESS
        && keypad_val != STAR
        && keypad_val != POUND) {
        printf("[DEBUG] keypad_val: %d \n", keypad_val);
        buf[*keys_entered] = (keypad_val == KEYPAD_ZERO) ? 0 : keypad_val;
        (*keys_entered)++;
        printf ("Char %d taken in! %d keys entered \n", keypad_val, *keys_entered);
        if (*keys_entered == NUM_CHARS_PWM) {
            uint32_t out_val = 0;
            for (i = 0; i < *keys_entered; i++) {
                out_val *= 10;
                out_val += buf[i];
            }
            if (out_val > 100) {
            printf("Invalid duty cycle of %d! Saturating the value to 100 \n", out_val);
            out_val = 1000;
            } else {
                printf("Duty cycle of %d%%!, buffer is: %d%d%d \n", out_val, buf[0], buf[1], buf[2]);
                out_val *= 10;
            }
            *duty_cycle_thousandths = out_val;
            *keys_entered = 0;
            for (i = 0; i < NUM_CHARS_PWM; i++) {
                buf[i] = 0;
            }
            return;
        }
    }
}
#undef KEYPAD_ZERO
#undef NUM_CHARS_PWM
#undef INVALID_KEYPRESS
