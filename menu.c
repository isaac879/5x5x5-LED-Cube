#include <stm32f4xx.h>
#include "delay.h"
#include "LED.h"
#include <stdio.h>
#include "ADCDAC.h"
#include <math.h>
#include "usart.h"
#include "Switch.h"

/*---------------------------------------------------------------------*/
void Enable_ALl_Clocks(void)
{
		RCC->AHB1ENR  |= RCC_AHB1ENR_GPIOAEN;    //PortA clock enable
   	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOBEN;		 //PortB clock enable
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;		 //PortC clock enable
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIODEN;		 //PortD clock enable
		RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOEEN;		 //PortE clock enable
}
/*---------------------------------------------------------------------*/
void Init_Init(void)
{
	SysTick_Init();					//Initialises the system clock.
	Init_ADC();
	//Init_ADC1(); 						//Initialises the ADC.
	//Init_DAC2();						//Initialises the DAC.
	//LCD_Init();  						//Initialises the LCD.
	//config_UART2 (115200);	//Sets baud rate to the maximum speed
	Enable_ALl_Clocks();		//Enables all the port clocks
	LEDinit();							//Initialises the LED's.
}
/*---------------------------------------------------------------------*/
















