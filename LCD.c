#include "stm32f4xx.h"
#include "LCD.h"
#include "delay.h"
#include <stdio.h>
#include "LED.h"

/*-----------------------------------------------------------------------
Make Bits 8, 10, 12, 14, 15 of PORT E inputs and 11, 12, 14 of port B inputs.
-----------------------------------------------------------------------*/
void Config_portE_B_Input(void)
{
	 LCD_PORT->MODER    &= ~(                 
				(3UL << 2*8) |
				(3UL << 2*10) |                      
				(3UL << 2*12) |                       
				(3UL << 2*14) |
				(3UL << 2*15) );  						 //PE: 8..15 = input (00)
	
	GPIOB->MODER    &= ~(                 
				(3UL << 2*11) |
				(3UL << 2*12) |
				(3UL << 2*14) );  						 //PB: 11, 12, 14 = input (00)
}
/*-----------------------------------------------------------------------
Make Bits 8, 10, 12, 14, 15 of PORT E and 11, 12, 14 of port B outputs.
-----------------------------------------------------------------------*/
void Config_portE_B_Output(void)
{

	 LCD_PORT->MODER    |= (  
				(1UL << 2*8) |	
				(1UL << 2*10) |                      
				(1UL << 2*12) |                       
				(1UL << 2*14) |
				(1UL << 2*15) );  						 //PE: 8..15 = output (01) 
	
	 GPIOB->MODER    |= (  
				(1UL << 2*11) |	
				(1UL << 2*12) |
				(1UL << 2*14) );  						 //PB: 11, 12, 14 = output (01) 
}
/*-----------------------------------------------------------------------
Initialise LCD Pins.
-----------------------------------------------------------------------*/
void LCD_Init(void)
{
		RCC->AHB1ENR  |= ((1UL <<  4) );         // Enable GPIOE clock 
   	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOBEN;		 //PortB clock enable
	//Setup LCD Control Pins.
	//Bits 9,11,13 as inputs : clear bits  first
	GPIOE->MODER    &= ~(
				(3UL << 2*9) |
				(3UL << 2*11) |
				(3UL << 2*13) );
	
	//Bits 9,11,13 as outputs.
	GPIOE->MODER    |=  (
				(1UL << 2*9) |
				(1UL << 2*11) |
				(1UL << 2*13) );   
	
	// Setup LCD Data Bus PortE[8:15]
	Config_portE_B_Input();		// Clear all pins first.
	Config_portE_B_Output();	
	
	//PE: 3,4,5,8..15 is output Push-Pull.
  	LCD_PORT->OTYPER   &= ~(   
				(1UL << 8) |                 
				(1UL << 9) |
				(1UL << 10) |
				(1UL << 11) |                       
				(1UL << 12) |                       
				(1UL << 13) |
				(1UL << 14) |
				(1UL << 15) ); 
				
		//PB: 11, 12, 14 is output Push-Pull.
	 GPIOB->OTYPER   &= ~(  
				(1UL << 2*11) |	
				(1UL << 2*12) |
				(1UL << 2*14) ); 				
				
	//PE: 3,4,5,8..15 is 50MHz Fast Speed.								 
  	LCD_PORT->OSPEEDR  &= ~(  
				(3UL << 2*8) |                 
				(3UL << 2*9) |
				(3UL << 2*10) |
				(3UL << 2*11) |                       
				(3UL << 2*12) |                       
				(3UL << 2*13) |                    
				(3UL << 2*14) |
				(3UL << 2*15)	);
				
			GPIOB->OSPEEDR   &= ~(  
				(3UL << 2*11) |	
				(3UL << 2*12) |
				(3UL << 2*14) ); 
				
	LCD_PORT->OSPEEDR  |=  (   
				(2UL << 2*8) |                 
				(2UL << 2*9) |
				(2UL << 2*10) |
				(2UL << 2*11) |                       
				(2UL << 2*12) | 
				(2UL << 2*13) | 
				(2UL << 2*14) | 
				(2UL << 2*15) ); 
				
		GPIOB->OSPEEDR   &= ~(  
				(2UL << 2*11) |	
				(2UL << 2*12) |
				(2UL << 2*14) ); 
				
	//PE: 8,9,10,11..15 is Disabled Pull up-down.								 
  	LCD_PORT->PUPDR    &= ~(   
				(3UL << 2*8) |                 
				(3UL << 2*9) |
				(3UL << 2*10) |
				(3UL << 2*11) |                       
				(3UL << 2*12) |                     
				(3UL << 2*13) |
				(3UL << 2*14) |
				(3UL << 2*15) );   
				
			GPIOB->PUPDR	   &= ~(  
				(2UL << 2*11) |	
				(2UL << 2*12) |
				(2UL << 2*14) );						

    	BitClr(LCD_E);          //clear enable
			BitClr(LCD_RW);					// write
    	BitClr(LCD_RS);         // command

    	delay_nus(3000);        //delay for LCD to initialise.
    	LCD_DATA(0x38,CMD);     //set to 8 bit interface, 2 line and 5*8 font
    	LCD_DATA(0x0C,CMD);     //cursor off
			LCD_DATA(0x10,CMD);
			LCD_CLR;          		 	//clear display
    	LCD_DATA(0x06,CMD);     //move cursor right after write
			LCD_HOME;								//return home
}
/*---------------------------------------------------------------------*/
void WaitLCDBusy(void) //needs updating! Maybe replace with Davey code before we used busy bit
{

  int busybit;
	
	BitClr(LCD_RS);											//Sets it to instruction command.
	BitSet(LCD_RW);											//Sets read mode.
	Config_portE_B_Input(); 						//Configues port E as an input.
	
	do
	{
		BitSet(LCD_E);  									//Enable LED data line
		BitClr(LCD_E);  									//Disable LED data line
		busybit = GPIOE->IDR;             //Sets busybit to the register.
	} while((busybit & (1<<8)) !=0);  	//Checks the busy bit and exits if not busy.
	
	Config_portE_B_Output(); 						//Configues port E and B as outputs.
	BitClr(LCD_RW); 										//Sets write mode.
}
/*---------------------------------------------------------------------*/
//shift to correct positions......
void LCD_DATA(unsigned char data,unsigned char type)
{
	WaitLCDBusy();             			//Test LCD for busy. 

	LCD_PORT->BSRRH |= 0xFF00;			// Clear data bits
	GPIOB->BSRRH |= 0xFF00;					// Clear data bits
// Set data bits
	GPIOE->BSRRL |= ((data & 0x01)<<15);
	GPIOE->BSRRL |= (((data & 0x010)>>4)<<14);
	GPIOE->BSRRL |= (((data & 0x020)>>5)<<12);
	GPIOE->BSRRL |= (((data & 0x040)>>6)<<10);
	GPIOE->BSRRL |= (((data & 0x080)>>7)<<8);
	
	GPIOB->BSRRL |= (((data & 0x02)>>1)<<11);
	GPIOB->BSRRL |= (((data & 0x04)>>2)<<14);
	GPIOB->BSRRL |= (((data & 0x08)>>3)<<12);

	//delay_nus(8);        						//Small delay

	if(type == CMD)
	{
		BitClr(LCD_RS);       				//Command mode
	} 
	else 
	{
		BitSet(LCD_RS);          			//Charactar/Data mode
	}

	BitSet(LCD_E);         					//Enable LED data line
	delay_nus(1);            				//Small delay
	BitClr(LCD_E);         					//Disable LED data line
}
/*-----------------------------------------------------------------------
Displays text on the LCD. x specifies the number of spaces 
it will be shifted right and y specifies line 1 or line 2.
-----------------------------------------------------------------------*/
void LCDString (char StringText[], int x, int y)
{
	int n;	
	int s=16;
	int i;

	LCD_DATA((LINE1|LINE2*y + x), CMD); 		//Sets position text will be displayed.
	
	for (n=0; StringText[n] !=0; n++){}			//Sets n to equal the number of elements in the array.
	
	if (n>16)
	{
		for (s=16; StringText[s] !=' '; s--){} //Finds the position last space that would be displayed on the first line.		
	}
	
	for (i=0; StringText[i] !=0; i++)        //Loops though the array of text and displays it then exits when it reaches the end.
	{
		
		LCD_DATA(StringText[i],TXT);					 //Displays the element in the array corresponding to i.
		
		if (i==s)
		{
			y=1;																	//Sets y to 1 so it will start to display on line 2.
			LCD_DATA((LINE1|LINE2*y + x), CMD);		//Changes to line 2.
		} 																			//End of if statment
	} 																				//End of for loop.			
}
/*-----------------------------------------------------------------------
Changes an int into a char array and displays it on the LCD.
-----------------------------------------------------------------------*/
void LCDNumber (int value, int x, int y)
{
	int n;	
	int s=16;
	int i;
	char string[10];     										//The char array that the number will be stored in.
		
	sprintf(string, "%d", value);					//Converts the value to a char array.
	
	LCD_DATA((LINE1|LINE2*y + x), CMD); 		//Sets position text will be displayed.
	
	for (n=0; string[n] !=0; n++){}			//Sets n to equal the number of elements in the array.
	
	if (n>16)
	{
		for (s=16; string[s] !=' '; s--){} //Finds the position last space that would be displayed on the first line.		
	}
	
	for (i=0; string[i] !=0; i++)        //Loops though the array of text and displays it then exits when it reaches the end.
	{
		LCD_DATA(string[i],TXT);					 //Displays the element in the array corresponding to i.
		
		if (i==s)
		{
			y=1;																	//Sets y to 1 so it will start to display on line 2.
			LCD_DATA((LINE1|LINE2*y + x), CMD);		//Changes to line 2.
		} 																			//End of if statment
	} 																				//End of for loop.			
}
/*---------------------------------------------------------------------*/
void display_variable(int number)
{
	char string[10];     							//The char array that the number will be stored in.
	sprintf(string, "%d", number);		//Converts the number to a char array.
	LCDVoltage(string);               //Displays the char array on the LCD.
}
/*---------------------------------------------------------------------*/

