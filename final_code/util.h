#ifndef UTIL_H
#define UTIL_H

#include "msp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

enum off_on {
    OFF = 0,
    ON = 1,
};

enum bool_t {
    false = 0,
    true = 1,
};

void Systick_ms_delay(uint16_t ms_delay);
void Systick_us_delay(uint16_t ms_delay);

#endif /* UTIL_H */
