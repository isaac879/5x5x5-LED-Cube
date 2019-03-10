#ifndef __LCD_H
#define __LCD_H

#define LCD_PORT GPIOE    //LCD DATA PORT : 8 data line bit 8-15
#define LCD_OUT GPIOE->ODR
#define LCD_IN	GRIOE->IDR

#define LCD_RS   9        //LCD Command/Data Control
#define LCD_RW	 11				//LCD Read/Write Select
#define LCD_E    13       //LCD Enable Line

#define CMD 0
#define TXT 1
#define CLEAR	1
#define HOME	2
#define READ 1
#define WRITE 0
#define LEFT 0
#define RIGHT 1

#define LINE1    0x80        // Start address of first line
#define LINE2    0xC0        // Start address of second line

#define BitClr(bit) 	(GPIOE->BSRRH |= (1<<bit))
#define BitSet(bit) 	(GPIOE->BSRRL |= (1<<bit))
#define LCD_CLR				(LCD_DATA(CLEAR,CMD))
#define LCD_HOME			(LCD_DATA(HOME,CMD))

void WaitLCDBusy(void);
void LCD_Init(void);
void LCD_DATA(unsigned char nyb,unsigned char type);
void Config_portE_B_Input(void);
void Config_portE_B_Output(void);
void LCDString (char StringText[], int x, int y);
void display_variable(int number);
void LCDVoltage (char StringText[]);
void Voltage_Bar(int number);
void LCDNumber (int value, int x, int y);

#endif
