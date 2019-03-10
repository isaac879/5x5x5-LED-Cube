#include "STM32F4xx.h"
#include "LCD.h"
#include "delay.h"
#include <math.h>
#define pi (3.141592653589793)
int direction=0; 
int GlobalCounter=0;
/*----------------------------------------------------------------------------
  Intializing the ADC1 with temperatuer sensor as input (12-bit precision)
 *----------------------------------------------------------------------------*/
void Init_ADC1(void){
	
	//Enable the clock for ADC module
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;
	
	//Set the prescaler for the clock
	RCC->CFGR|=RCC_CFGR_PPRE2_DIV2;
	ADC->CCR|=ADC_CCR_ADCPRE_0;
	
	//Power up the ADC module
	ADC1->CR2|=ADC_CR2_ADON;
	
	//480	cycles, better accuracy than 3 cycles
	ADC1->SMPR1|=ADC_SMPR1_SMP16;
	
	//Enable the temperature sensor
	ADC->CCR|=ADC_CCR_TSVREFE;
	
	//Select channel 16 as input (temperature sensor)
	ADC1->SQR3|=ADC_SQR3_SQ1_4;
}
/*----------------------------------------------------------------------------
  Start the ADC conversion and return the reading
 *----------------------------------------------------------------------------*/
uint16_t Get_ADC1(){

	//Software trigger the conversion
	ADC1->CR2|=ADC_CR2_SWSTART;
	
	//Wait for the completion of the conversion
	while(!(ADC1->SR&(1UL<<1))){}
		
	//Return the reading value	
	return ADC1->DR;
}
/*----------------------------------------------------------------------------
  Start the ADC conversion and return the averaged value of reading
 *----------------------------------------------------------------------------*/
uint16_t Get_Average_ADC1(uint8_t times){
	uint8_t t;
	uint32_t temp=0;
	
	for(t=0;t<times;t++){
		temp+=Get_ADC1();
	}
	return temp/times;
}
/*----------------------------------------------------------------------------
  Intializing the DAC2 as 12-bit right alignment DAC
	And the corresponding GPIO
 *----------------------------------------------------------------------------*/
void Init_DAC2(void){
	
	//Enable the clock for DAC module and GPIO Port A
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR|=RCC_APB1ENR_DACEN;
	
	//Configure the PoRT A pin 5 to be the Analogue
	GPIOA->MODER|=GPIO_MODER_MODER5;
	GPIOA->PUPDR&=~(GPIO_PUPDR_PUPDR5);

	//Enable the DAC
	DAC->CR|=DAC_CR_EN2;
	
	//Write to the DAC channel1 12-bit right-aligned data holding register
	DAC->DHR12R2=0;
}
/*----------------------------------------------------------------------------
	Read the value from the temperature sensor than output the value to DAC
	The voltage at GPIOA pin 5 should be around the same as the output of 
	temperature sensor
 *----------------------------------------------------------------------------*/
int Test_temp (void)
{
		uint16_t temperature_reading;
	
		temperature_reading=Get_ADC1();	
		DAC->DHR12R2=temperature_reading;
	
		return temperature_reading;
}
/*----------------------------------------------------------------------------
	Generates a ramp signal
 *----------------------------------------------------------------------------*/
 int Rampwave (void)
 {
		DAC->DHR12R2=-0xfff*GlobalCounter/3000;
	 
		 if(GlobalCounter>=3000)
		 {
			 GlobalCounter=0;
		 }
		 
		 GlobalCounter=GlobalCounter+5;
		 
		 return GlobalCounter;
 }
/*----------------------------------------------------------------------------
	Generates a Sinewave
 *----------------------------------------------------------------------------*/
  int Sinewave (void)
 {
	int sine;
	 int Half_Peak=0xFFF/2;
		DAC->DHR12R2=Half_Peak*sin(GlobalCounter*(pi/180))+Half_Peak;
		sine = Half_Peak*sin(GlobalCounter*(pi/180))+Half_Peak;
		
	 	sine = (sine*3000)/(0xfff);
		GlobalCounter=GlobalCounter+2;
	 return sine;
 }

 /*----------------------------------------------------------------------------
	Generates a Triangle wave
 *----------------------------------------------------------------------------*/
  int Trianglewave (void)
 {
		DAC->DHR12R2=(0x0fff)*GlobalCounter/3000;
	 
		if(GlobalCounter>=3000)
		{
			direction=1;
		}
		if(GlobalCounter<=0)
		{
			direction=0;
		}
	 
		if(direction==0)
		{
			GlobalCounter=GlobalCounter+50;
		} 
		else
		{
			GlobalCounter=GlobalCounter-50;
		}
	 return GlobalCounter;
 }
  /*----------------------------------------------------------------------------
	Generates a Square wave
 *----------------------------------------------------------------------------*/
  int Squarewave (void)
 {
		DAC->DHR12R2=(0xfff)*GlobalCounter/3000;
	 
		if(direction==0)
		{
			GlobalCounter=3000;
		} 
		else if(direction==70)
		{
			GlobalCounter=0;
		}
		
		if(GlobalCounter>=3000)
		{
			direction=direction+1;
		}
			if(GlobalCounter<=0)
		{
			direction=direction-1;
		}
	 
	 return GlobalCounter;
 }
  /*----------------------------------------------------------------------------*/
 void Init_ADC1_MyOne(void) //seems to work on his lecture slides about 43 
 {
	 RCC->AHB1ENR |=((1<<4)|(1<<3)|(1<<2)); //Switches on clocks for ports 
	 RCC->APB2ENR |=(1<<8); //Switches on clocks for the ADC
	 GPIOC->MODER|=(3<<(4*2));
	 ADC1->SQR3|=14;
	 ADC1->CR2|=0x01; 
 }
 
int Get_ADC1_MyOne(void) //seems to work on his lecture slides about 43 
 {
	 ADC1->SQR3|=14;
	 return Get_ADC1()*3000/0xfff;
 }
