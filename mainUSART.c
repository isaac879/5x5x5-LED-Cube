#include <stdio.h>
#include <stm32f4xx.h>
#include "delay.h"													//containsyour previously created delay routines
#include "LCD.h"													  //contains your previously created LCD routines
#include "LED.h"														//contains your previously created LEDroutines
#include "usart.h"													//contains USART routines


int main(void)
{																						//!!!Remember CLOCKS have to be enabled before initialization routine.
RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; 		  	// enable the clock to GPIOD
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;			  // enable the clock to GPIOA
SysTick_Init();															//defined in delay.c
LCD_Init();																	//defined in LCD.c
config_UART2();															//defined in uart.c

	while(1)
	{
		int i;
		//USART_SendData('A');										// defined in usart.c
		printf("Hello World \r\n");
		while(i--);															//short delay
		i=0x1ffffff;
		
	}
}

