#include "stm32f4xx.h"
#include "LCD.h"
#include "ADCDAC.h"
#include "switch.h"
#include "delay.h"
	
	int countx=0;
	int county=0;
	int countz=0;
	
/*---------------------------------------------------------------------*/
int ultrasonic_sensor_echo_x(void)
{
	int input;
	input = GPIOD->IDR;
	input = input & 0x01; 	//Masks bit 0
	
	return input;							//Returns the masked bit
}
/*---------------------------------------------------------------------*/
int ultrasonic_sensor_echo_y(void)
{
	int input;
	input = GPIOD->IDR;
	input = (input & 0x04)>>2; 	//Masks bit 2
	
	return input;							//Returns the masked bit
}
/*---------------------------------------------------------------------*/
int ultrasonic_sensor_echo_z(void)
{
	int input;
	input = GPIOD->IDR;
	input = (input & 0x08)>>3; 	//Masks bit 3
	
	return input;							//Returns the masked bit
}
/*---------------------------------------------------------------------*/
void Trigger_On(void)
{
	GPIOD->ODR |=(1UL << 1);
}
/*---------------------------------------------------------------------*/
int Ultrasonic_distance(void)
{
	int l;
	int count=0;
	
	Trigger_On();
	delay_nus(50);
	Trigger_Off();

	for(l=0; l<3000000; l++)
	{
		if(ultrasonic_sensor_echo_x()==1)
		{
			count++;
			if(count>=100000)
			{
				return -1;
			}
		}
	}
	return count/325;
}
/*---------------------------------------------------------------------*/
void Ultrasonic_distance_xyz(void)
{
	int l;
	countx=0;
	county=0;
	countz=0;
	
	Trigger_On();
	delay_nus(50);
	Trigger_Off();

	for(l=0; l<50000; l++)//test the quickest speed I can get
	{
		if(ultrasonic_sensor_echo_x()==1)
		{
			countx++;		
		}
		
		if(ultrasonic_sensor_echo_y()==1)
		{
			county++;	
		}
		
		if(ultrasonic_sensor_echo_z()==1)
		{
			countz++;	
		}
		
		if(countx>=100000)
		{
			countx=-1;
		}
		if(county>=100000)
		{
			county=-1;
		}
		if(countz>=100000)
		{
			countz=-1;
		}
	}
	//return countx/325;
}
/*---------------------------------------------------------------------*/
int Return_Ultrasonic (int xyz)
{
	if(xyz==0)
	{
		return countx/60;//92.5;
	}
	else if(xyz==1)
	{
		return county/60;//92.5;
	}
	else if(xyz==2)
	{
		return countz/60;//92.5;
	}
	else
	{
		return -1;
	}
}
/*---------------------------------------------------------------------*/
void Trigger_Off(void) 
{
	GPIOD->ODR &=~(1UL << 1);
}
/*---------------------------------------------------------------------*/
int Reed_SwitchB(void)	
{
	int input;
	GPIOC->PUPDR &=~ (3UL << 2*13); //Clears pin 13
	GPIOC->PUPDR |= (1UL << 2*13); 	//Set pull up (01)
	
	input = GPIOC->IDR;
	input = (input & 0x02000)>>13; 	//Masks bit 13
	
	return input;										//Returns the masked bit
}
/*---------------------------------------------------------------------*/
int Reed_SwitchA(void)	
{
	int input2;
	GPIOE->PUPDR &=~ (3UL << 2*5); //Clears pin 5
	GPIOE->PUPDR |= (1UL << 2*5); 	//Set pull up (01)
	
	input2 = GPIOE->IDR;
	input2 = (input2 & 0x020)>>5; 	//Masks bit 5
	
	return input2;									//Returns the masked bit
}
/*---------------------------------------------------------------------*/
int UserButton(void)	
{
	int input;
	
	input = GPIOA->IDR;
	input &= 0x01; 					//Masks the first bit
	
	return input;						//Returns the masked bit
}
/*---------------------------------------------------------------------*/
	int analogue_direction_1(void)
	{
		int FB;
		int LR;
		FB=Get_PC5_Val();
		LR=Get_PC4_Val();
		
		if(FB<1000 && LR<3500 && LR>500){
			return forward;
		}else if(FB>3000 && LR<3500 && LR>500){
			return backward;
		}else if(LR<1000 && FB<3500 && FB>500){
			return left;
		}else if(LR>3000 && FB<3500 && FB>500){
			return right;
		}
		return 0;
	}
/*---------------------------------------------------------------------*/
	int analogue_direction_2(void)
	{
		int UD;
		UD=Get_PC1_val();
		
		if(UD<1000){
			return up;
		}else if(UD>3000){
			return down;
		}
		return 0;
}
/*---------------------------------------------------------------------*/
