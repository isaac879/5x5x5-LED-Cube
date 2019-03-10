#ifndef __menu_H
#define __menu_H

#include <stm32f4xx.h>
#include "delay.h"
#include "LCD.h"
#include "LED.h"
#include <stdio.h>
#include "ADCDAC.h"
#include <math.h>
#include "usart.h"
#include "Switch.h"

int Set_Hold(void);
int Baud_Rate (int USART_Select);
void Enable_ALl_Clocks(void);
void Init_Init(void);
	
#endif
