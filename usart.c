#include "usart.h"
#include <stdio.h>
#include <stm32f4xx.h>
#include "menu.h"

int Q=5;

void config_UART2 (int Baud_Rate)
{
	unsigned int temp;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;		// enable the clock to USART2
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 		// enable the clock to GPIOA

	CLEAR_BIT(GPIOA->MODER,3UL<<(TX*2));
	SET_BIT(GPIOA->MODER,2UL<<(TX*2));			// Set TX bit to Alternate function
	CLEAR_BIT(GPIOA->MODER,3UL<<(RX*2));
	SET_BIT(GPIOA->MODER,2UL<<(RX*2)); 			//set RX bit to Alternate function
	
	CLEAR_BIT(GPIOA->OTYPER, 1UL<<TX);			// set to push-pull
	CLEAR_BIT(GPIOA->OTYPER, 1UL<<RX);			// set to push-pull
	
	CLEAR_BIT(GPIOA->OSPEEDR, 3UL<<(TX*2));	// 2MHz speed
	CLEAR_BIT(GPIOA->OSPEEDR, 3UL<<(RX*2));	// 2MHz speed
	
  CLEAR_BIT(GPIOA->PUPDR, 3UL<<(TX*2));		// no pullup or pulldown
  CLEAR_BIT(GPIOA->PUPDR, 3UL<<(RX*2));		// no pullup or pulldown

	GPIOA->AFR[0] |= 0x07<<(TX*4);					// Set Alternate Function Register for pin2
	GPIOA->AFR[0] |= 0x07<<(RX*4);					// Set Alternate Function Register for pin3
	
	CLEAR_BIT(USART2->CR2, (1<<12|1<<13));	// Clear STOP bits = 1 STOP BIT
	CLEAR_BIT(USART2->CR1, 1<<15);					// 16 bit oversampling
	CLEAR_BIT(USART2->CR1, 1<<12);					// 1 start bit 8 Data bits
	CLEAR_BIT(USART2->CR1, 1<<10);					// Disable PARITY
	CLEAR_BIT(USART2->CR1, 1<<9);						// EVEN Parity
	
	SET_BIT(USART2->CR1, 1<<3); 						// Transmitter enable
	SET_BIT(USART2->CR1, 1<<2);							// Reciever enable
	
  temp = (((168000000/4)<<5) / (16 * Baud_Rate));//twice BRR needed for LSB accuracy 0.5%

  USART2->BRR = (temp>>1) + (temp&0x1);
	SET_BIT(USART2->CR1, 1<<13);							//USART Enable
}
/*---------------------------------------------------------------------*/
void USART_SendData(uint16_t Data)
{
  USART2->DR = (Data & (uint16_t)0x01FF);
}
/*---------------------------------------------------------------------*/
uint16_t USART_ReciveData(void)
{
   return (USART2->DR & (uint16_t)0x01FF);
}

/*---------------------------------------------------------------------*/
unsigned int USART_Status(void)
{
	unsigned int status;
  status = (USART2->SR & (1<<6));
  
  return status;
}
/*---------------------------------------------------------------------*/
unsigned int USARTRecive_Status(void)
{
	unsigned int status;
  status = ((USART2->SR & (1<<5))>>5);
  
  return status;
}
/*-----------------------------------------------------------------------
	Displays a bar on the USART proportional to the voltage.
-----------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
//Use no semihosting
#if 1
#pragma import(__use_no_semihosting)
struct __FILE
{  
	int handle;
};
FILE __stdout;

void _sys_exit(int x)
{
	x = x;
}
#endif

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData((uint8_t) ch);

  /* Loop until the end of transmission */
  while ((USART2->SR & (1<<6)) == 0){}
  return ch;
}
/*---------------------------------------------------------------------*/
