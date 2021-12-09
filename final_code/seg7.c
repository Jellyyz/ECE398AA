#include "seg7.h"

struct segments {
    int a, b, c, d, e, f, g;
} seg[10] = {
    // 0
    {.a = ON , .b = ON , .c = ON , .d = ON , .e = ON , .f = ON , .g = OFF},
    // 1
    {.a = OFF, .b = ON , .c = ON , .d = OFF, .e = OFF, .f = OFF, .g = OFF},
    // 2
    {.a = ON , .b = ON , .c = OFF, .d = ON , .e = ON , .f = OFF, .g = ON },
    // 3
    {.a = ON , .b = ON , .c = ON , .d = ON , .e = OFF, .f = OFF, .g = ON },
    // 4
    {.a = OFF, .b = ON , .c = ON , .d = OFF, .e = OFF, .f = ON , .g = ON },
    // 5
    {.a = ON , .b = OFF, .c = ON , .d = ON , .e = OFF, .f = ON , .g = ON },
    // 6
    {.a = ON , .b = OFF, .c = ON , .d = ON , .e = ON , .f = ON , .g = ON },
    // 7
    {.a = ON , .b = ON , .c = ON , .d = OFF, .e = OFF, .f = OFF, .g = OFF},
    // 8
    {.a = ON , .b = ON , .c = ON , .d = ON , .e = ON , .f = ON , .g = ON },
    // 9
    {.a = ON , .b = ON , .c = ON , .d = OFF, .e = OFF, .f = ON , .g = ON },
};

/*
init_segment_leds
Initializes the segment LEDs
Inputs: None
Outputs: None
Side Effects: Changes the associated pins and the segment LEDs
*/
void init_segment_leds() {
    // Display 0
    P2SEL0 &= ~(BIT3 | BIT4 | BIT5 | BIT6);
    P2SEL1 &= ~(BIT3 | BIT4 | BIT5 | BIT6);
    P3SEL0 &= ~(BIT0 | BIT2 | BIT3);
    P3SEL1 &= ~(BIT0 | BIT2 | BIT3);
    P2DIR  |=  (BIT3 | BIT4 | BIT5 | BIT6); // Output 
    P3DIR  |=  (BIT0 | BIT2 | BIT3); // Output 

    // Display 1
    P5SEL0 &= ~(BIT0 | BIT1 | BIT2 | BIT4 | BIT5 | BIT6 | BIT7);
    P5SEL1 &= ~(BIT0 | BIT1 | BIT2 | BIT4 | BIT5 | BIT6 | BIT7);
    P5DIR  |=  (BIT0 | BIT1 | BIT2 | BIT4 | BIT5 | BIT6 | BIT7); // Output

    // Initialize to 0
    set_seg0(0);
    set_seg1(0);
}

/*
set_seg0
Set segment 0 to a number (from 0 to 9)
Inputs: Number to set the segment to
Outputs: None
Side Effects: Changes P2OUT and P3OUT
*/
void set_seg0 (uint32_t n) {
    uint8_t p2o, p3o;
    p2o = P2OUT;
    p3o = P3OUT;

    (seg[n].a == ON)? (p2o |= BIT3): (p2o &= ~BIT3);
    (seg[n].b == ON)? (p2o |= BIT4): (p2o &= ~BIT4);
    (seg[n].c == ON)? (p2o |= BIT5): (p2o &= ~BIT5);
    (seg[n].d == ON)? (p2o |= BIT6): (p2o &= ~BIT6);
    (seg[n].e == ON)? (p3o |= BIT0): (p3o &= ~BIT0);
    (seg[n].f == ON)? (p3o |= BIT2): (p3o &= ~BIT2);
    (seg[n].g == ON)? (p3o |= BIT3): (p3o &= ~BIT3);

    P2OUT = p2o;
    P3OUT = p3o;
}

/*
set_seg1
Set segment 1 to a number (from 0 to 9)
Inputs: Number to set the segment to
Outputs: None
Side Effects: Changes P5OUT
*/
void set_seg1 (uint32_t n) {
    uint8_t p5o;
    p5o = P5OUT;

    (seg[n].a == ON)? (p5o |= BIT0): (p5o &= ~BIT0);
    (seg[n].b == ON)? (p5o |= BIT1): (p5o &= ~BIT1);
    (seg[n].c == ON)? (p5o |= BIT2): (p5o &= ~BIT2);
    (seg[n].d == ON)? (p5o |= BIT4): (p5o &= ~BIT4);
    (seg[n].e == ON)? (p5o |= BIT5): (p5o &= ~BIT5);
    (seg[n].f == ON)? (p5o |= BIT6): (p5o &= ~BIT6);
    (seg[n].g == ON)? (p5o |= BIT7): (p5o &= ~BIT7);

    P5OUT = p5o;
}

/*
set_seg_leds
Sets the 2 segment LEDs to display a 2 digit number
Inputs: 2 digit number
Outputs: None
Side Effects: Sets the 2 LEDs
*/
void set_seg_leds (uint32_t n) {
    if (n > 99) {
        return;
    }
    set_seg0(n / 10);
    set_seg1(n % 10);
}
