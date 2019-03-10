#include "stm32f4xx.h"
#include "delay.h"
#include <stdio.h>

void Init_ADC(void){
	
	RCC->AHB1ENR |=(1<<2); 	
	RCC->APB2ENR |=RCC_APB2ENR_ADC1EN; 				//Enables clock for the ADC1
	RCC->APB2ENR |=RCC_APB2ENR_ADC2EN;				//Enables clock for the ADC2
	RCC->APB2ENR |=RCC_APB2ENR_ADC3EN;				//Enables clock for the ADC3
	
	GPIOC->MODER |=(3<<(2*1));								//Sets PC1 as analogue
	GPIOC->MODER|=(3<<(2*4)); 								//Sets PC4 as analogue
	GPIOC->MODER |=(3<<(2*5));								//Sets PC5 as analogue
	GPIOC->MODER |=(3<<(2*2));								//Sets PC2 as analogue
	
	ADC1->SQR3|=14; 													//Conversion on PC4
	ADC2->SQR3|=15;														//Conversion on PC5
	//ADC3->SQR3|=12;														//Conversion on PC2
	ADC3->SQR3|=11;														//Conversion on PC1

	//Turns on ADC
	ADC1->CR2|=0x01; 												
	ADC2->CR2|=0x01;
	ADC3->CR2|=0x01;
}

/*----------------------------------------------------------------------------
  Start the ADC conversion and return the reading
 *----------------------------------------------------------------------------*/
uint16_t Get_PC4_Val(){

	//Software trigger the conversion
	ADC1->CR2|=ADC_CR2_SWSTART;
	
	//Wait for the completion of the conversion
	while(!(ADC1->SR&(1UL<<1))){}
		
	//Return the reading value	
	return ADC1->DR;

}
/*-----------------------------------------------------------------------------*/
uint16_t Get_PC5_Val(){

	//Software trigger the conversion
	ADC2->CR2|=ADC_CR2_SWSTART;
	
	//Wait for the completion of the conversion
	while(!(ADC2->SR&(1UL<<1))){}
		
	//Return the reading value	
	return ADC2->DR;
}
/*-----------------------------------------------------------------------------*/
uint16_t Get_PC1_val(){
	//Software trigger the conversion
	ADC3->CR2|=ADC_CR2_SWSTART;
	
	//Wait for the completion of the conversion
	while(!(ADC3->SR&(1UL<<1))){}
		
	//Return the reading value	
	//ADC3->SQR3^=11;
	return ADC3->DR;
}
/*-----------------------------------------------------------------------------*/
//uint16_t Get_PC2_val(){
//	//Software trigger the conversion
//	ADC3->CR2|=ADC_CR2_SWSTART;
//	
//	//Wait for the completion of the conversion
//	while(!(ADC3->SR&(1UL<<1))){}
//		
//	//Return the reading value
//	//ADC3->SQR3^=12;
//	return ADC3->DR;
//}
///*-----------------------------------------------------------------------------*/

