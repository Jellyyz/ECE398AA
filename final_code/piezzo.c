#include "piezzo.h"

// To achieve a 50% duty cycle
struct note_3mhz_val {
    uint16_t h;
    uint16_t l;
} note_val_arr[] = {
    {.h = 5733,     .l = 2867},
    {.h = 4551,     .l = 2275},
    {.h = 3827,     .l = 1913},
    {.h = 3612,     .l = 1806},
    {.h = 3037,     .l = 1519},
    {.h = 2867,     .l = 1433},
    {.h = 2275,     .l = 1138},
};

int cur_tune = TUNE0;

// void play_tune_0(void);
void play_tune_1(void);

/*
init_piezzo
Initializes informantion used by the piezzo sounder
Inputs: None
Outputs: None
Side Effects: Changes pins used by the piezzo sounder and the 
registers of Timer A
*/
void init_piezzo() {
    // Select GPIO
    P2SEL0 |= BIT7;
    P2SEL1 &= ~BIT7;
    // Direction: Output
    P2DIR |= BIT7;

    TA0CCTL0 = 0x0;
    TA0CCTL4 = 0x00E0; // Reset-set mode

    set_tune(TUNE0);
}

/*
on_piezzo
Turns on the piezzo sounder
Inputs: None
Outputs: None
Side Effects: Changes Timer A and the sounder
*/
void on_piezzo() {
    // Start timer A_0
    // Outmode: Reset-set
    // SMCLK (3MHz), Up mode, clear
    // No interrupts
    // (0x0200) | (0x0010) | (0x0004);
    TA0CTL = 0x0214;
}

/*
off_piezzo
Turns off the piezzo sounder
Inputs: None
Outputs: None
Side Effects: Changes Timer A and the sounder
*/
void off_piezzo() {
    // Start timer A_0
    // Outmode: Reset-set
    // SMCLK (3MHz), Stop mode, clear
    // No interrupts
    // (0x0200) | (0x0000) | (0x0004);
    TA0CTL = 0x0204;
}

/*
set_note
Sets the note to be played
Inputs: Note to be played
Outputs: None
Side Effects: Changes Timer A registers
*/
void set_note(enum note n) {
    TA0CCR0 = note_val_arr[n].h;
    TA0CCR4 = note_val_arr[n].l;
}

/*
set_tune
Sets the tune to be played
Inputs: None
Outputs: None
Side Effects: Changes the global tune variable
*/
void set_tune(enum tune t) {
    cur_tune = t;
}

/*
play_tune
Plays the set tune
Inputs: None
Outputs: None
Side Effects: Plays the tune
*/
void play_tune() {
    (cur_tune == TUNE0) ? play_tune_0(): play_tune_1();
}

/*
play_tune_0
Plays tune 0
Inputs: None
Outputs: None
Side Effects: Plays tune 0
*/
void play_tune_0() {
    off_piezzo();
    set_note(B5);
    on_piezzo();
    Systick_ms_delay(800);

    off_piezzo();
    Systick_ms_delay(200);
    set_note(B5);
    on_piezzo();
    Systick_ms_delay(800);

    off_piezzo();
    Systick_ms_delay(200);
    set_note(B5);
    on_piezzo();
    Systick_ms_delay(400);

    off_piezzo();
    Systick_ms_delay(100);
    set_note(GSH5);
    on_piezzo();
    Systick_ms_delay(400);

    off_piezzo();
    Systick_ms_delay(100);
    set_note(E6);
    on_piezzo();
    Systick_ms_delay(1000);
    off_piezzo();
}

/*
play_tune_1
Plays tune 1
Inputs: None
Outputs: None
Side Effects: Plays tune 1
*/
void play_tune_1() {
    off_piezzo();
    set_note(C5);
    on_piezzo();
    Systick_ms_delay(200);

    off_piezzo();
    set_note(E5);
    on_piezzo();
    Systick_ms_delay(200);

    off_piezzo();
    set_note(G5);
    on_piezzo();
    Systick_ms_delay(200);
    
    off_piezzo();
    set_note(E5);
    on_piezzo();
    Systick_ms_delay(200);

    off_piezzo();
    set_note(C5);
    on_piezzo();
    Systick_ms_delay(200);

    off_piezzo();
    set_note(E5);
    on_piezzo();
    Systick_ms_delay(200);

    off_piezzo();
    set_note(G5);
    on_piezzo();
    Systick_ms_delay(200);
    
    off_piezzo();
    set_note(E5);
    on_piezzo();
    Systick_ms_delay(200);


    off_piezzo();
    set_note(C5);
    on_piezzo();
    Systick_ms_delay(400);

    off_piezzo();
    set_note(E5);
    on_piezzo();
    Systick_ms_delay(400);

    off_piezzo();
    set_note(C6);
    on_piezzo();
    Systick_ms_delay(800);
    off_piezzo();
}
