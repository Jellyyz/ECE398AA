#ifndef IR_H
#define IR_H

#include "util.h"

volatile uint16_t adcval;

void ADC_init(void); 
uint16_t read_ADC(void);
void set_adcval(uint16_t);

#endif /* IR_H */
