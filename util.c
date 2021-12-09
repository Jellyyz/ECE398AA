#include "util.h"

/*
Systick_ms_delay
Milisecond delay using systick
Inputs: miliseconds to delay by
Outputs: None
Side Effects: Changes Systick registers to generate a delay
*/
void Systick_ms_delay(uint16_t ms_delay){
    SysTick -> LOAD = ms_delay*3000 -1;
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000005;
    while((SysTick -> CTRL & 0x10000) == 0);
}

/*
Systick_us_delay
Microsecond delay using systick
Inputs: microseconds to delay by
Outputs: None
Side Effects: Changes Systick registers to generate a delay
*/
void Systick_us_delay(uint16_t ms_delay){
    SysTick -> LOAD = ms_delay*3 -1;
    SysTick -> VAL = 0;
    SysTick -> CTRL = 0x00000005;
    while((SysTick -> CTRL & 0x10000) == 0);
}
