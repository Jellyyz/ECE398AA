#ifndef TIMER32_H
#define TIMER32_H

#include "util.h"

volatile int t32_int_flag;

void init_t32(void);
// Enable and disable not necessary.
// void t32_enable(void);
// void t32_disable(void);

void t32_delay_seconds(int n);
void t32_delay_30s(void);
void T32_INT1_IRQHandler(void);

#endif /* TIMER32_H */
