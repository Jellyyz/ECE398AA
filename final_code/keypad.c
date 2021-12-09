#include "keypad.h"

#define ROW_PINS (BIT0 | BIT1 | BIT2 | BIT3)
#define COL_PINS (BIT4 | BIT5 | BIT6)
#define KEYPAD_PINS (ROW_PINS | COL_PINS)

/*
init_keypad
Initialize the information used by the keypad
Inputs: None
Outputs: None
Side Effects: Modifies pins used by the keypad
*/
void init_keypad() {
    P4SEL0 &= ~KEYPAD_PINS;
    P4SEL1 &= ~KEYPAD_PINS;
    P4DIR  &= ~KEYPAD_PINS; // Set cols to high Z (input) and rows to input
    P4REN  &= ~COL_PINS;
    P4REN  |=  ROW_PINS; // Enable row pull resistors
    P4OUT  &= ~COL_PINS;
    P4OUT  |=  ROW_PINS; // Configure and use the pull resistors
}

/*
read_keypad
Reads the keypad
Rows: Ports 4.0, 4.1, 4.2, 4.3
Cols: Ports 4.4, 4.5, 4.6
Inputs: None
Return: INVALID_KEYPRESS if nothing pressed
Side Effects: None
*/
int8_t read_keypad(void) {
    volatile uint8_t col;
    volatile uint8_t row;
    volatile int never_pressed = 1; // 0 if pressed, 1 if never pressed at all
    int8_t num_read;

    // Loop through the columns
    for (col = 0; col < NUM_COLS; col++) {
        // P4DIR = 0x00; // Set cols to high Z, Set rows as inputs
        P4DIR &= ~KEYPAD_PINS; // Set cols to high Z, Set rows as inputs
        P4DIR |=  (BIT4 << col);  // Set column to output
        P4OUT &= ~(BIT4 << col);  // Set column to LOW
        // Check for press
        Systick_ms_delay(5); // Give some delay before reading
        row = P4IN & ROW_PINS;
        // Wait for bouncing
        Systick_ms_delay(5);
        // Check if still pressed
        if ((P4IN & ROW_PINS) != 0x0F) {
            never_pressed = 0;
            // Wait for release
            while ((P4IN & ROW_PINS) != 0x0F);
            break;
        } else {
            continue;
        }
    }
    // Reset to high Z
    // P4DIR = 0x00;
    P4DIR &= ~KEYPAD_PINS;
    // Keypad not pressed
    if (never_pressed) {
        return INVALID_KEYPRESS;
    }
    // Wait for debounce
    // Systick_ms_delay(10);
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

/*
get_keypad
Reads 3 characters to generate a 2 digit value.
Inputs: None
Outputs: 2 digit value
Side Effects: None
*/
int8_t get_keypad() {
    int8_t keypad_val;
    uint32_t elems_keyed_in = 0;
    uint32_t buf[NUM_CHARS_VALUE];
    uint32_t i;

    for (i = 0; i < NUM_CHARS_VALUE; i++) {
        buf[i] = 0;
    }
    // printf("[DEBUG] Getting VALUE \n");
    while (1) {
        keypad_val = read_keypad();
        // printf("[DEBUG] val %d from keypad!", keypad_val);
        if (keypad_val == POUND) {
            // Done
            // printf("Pressed a #.\n");
            break;
        }
        if (keypad_val == STAR) {
            // printf("Pressed a *.\n");
            return -10; 
        }
        // Valid keypad input
        if (keypad_val != INVALID_KEYPRESS
            && keypad_val != POUND) {
            // printf("[DEBUG] keypad_val: %d \n", keypad_val);
            buf[elems_keyed_in] = (keypad_val == KEYPAD_ZERO) ? 0 : keypad_val;
            if (elems_keyed_in == NUM_CHARS_VALUE) {
                break;
            } else {
                elems_keyed_in++;
                // printf ("Char %d taken in! \n", elems_keyed_in);
            }
        }
    }
    // The elements will be keyed in from the element before null terminate to 0.
    uint32_t out_val = 0;
    for (i = 0; i < elems_keyed_in; i++) {
        out_val *= 10;
        out_val += buf[i];
    }
    if (out_val > 99) {
        // printf("Invalid value of %d! Saturating the value to 99 \n", out_val);
        out_val = 99;
    } else {
        // printf("Value of %d%%! \n", out_val);
    }
    return out_val;
}