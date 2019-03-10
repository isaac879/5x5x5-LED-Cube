#ifndef __ADCDAC_H
#define __ADCDAC_H

#include "stm32f4xx.h"

void Init_ADC1(void);
void Init_DAC2(void);
int Get_ADC1(void);
void DC_voltage (int mV);
uint16_t Get_PC1_val(void);
uint16_t Get_PC5_Val(void);
uint16_t Get_PC4_Val(void);
void Init_ADC(void);

#endif
