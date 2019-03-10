#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"

#define TX 2
#define RX 3

void config_UART2 (int Baud_Rate);
void USART_SendData(uint16_t Data);
unsigned int USART_Status(void);
unsigned int USARTRecive_Status(void);
uint16_t USART_ReciveData(void);
void USART_Voltage_Bar(int Voltage_Reading);
void Change_Baud_USART (void);

#endif

