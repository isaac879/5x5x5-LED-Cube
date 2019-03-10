#include "delay.h"
#include "LED.h"
#define ms_count SystemCoreClock/1000
#define us_count SystemCoreClock/1000000

static __IO uint32_t sysTickCounter;
/*---------------------------------------------------------------------*/
void SysTick_Init(void)
{
	while (SysTick_Config(us_count) != 0){} // One SysTick interrupt now equals 1us
}
/*---------------------------------------------------------------------*/
void SysTick_Handler(void)
{
	TimeTick_Decrement();
}
	/*---------------------------------------------------------------------*/
void TimeTick_Decrement(void)
{
	if (sysTickCounter != 0x00)
	{
		sysTickCounter--;
	}
}
/*---------------------------------------------------------------------*/
void delay_nus(u32 n)				//delay of n microseconds
{
	sysTickCounter = n;
	while (sysTickCounter != 0){}
}
/*---------------------------------------------------------------------*/
void delay_1ms(void)					//delay of 1 ms
{
	sysTickCounter = 1000;
	while (sysTickCounter != 0){}
}
/*---------------------------------------------------------------------*/
void delay_nms(u32 n)					//delay of n milliseconds
{
	while (n--)
	{
		delay_1ms();
	}
}
/*---------------------------------------------------------------------*/
