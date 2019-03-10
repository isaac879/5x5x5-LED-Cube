#include "LED.h"
#include "delay.h"
#include "stm32f4xx.h"
#include "switch.h"
#include <math.h>
#include <Stdlib.h>

int deg;
int deg2;
int deg3;
int deg4;
int analoguex=2;
int analoguey=2;
int analogue_level=2;
int start_once=0;
int snake_length=1;
int snake_controlx=2;
int snake_controly=2;
int snake_controlz=2;
int snake_direction=0;
int snake_up_down=0;
int food_position[3] = {0, 0, 0};
int s3, s4;
int first_move=0;
int cube_travel_posy=1; //global to remember where the cube is randomly travelling from 1 ~ 8
int x_ultrasonic=2;
int y_ultrasonic=2;
int z_ultrasonic=2;

int snake_array[125][3]= { //x, y, z (this is correct for the formatting of this array)
{2, 2, 2},
{2, 3, 2},
{2, 0, 0},
{3, 0, 0},
{4, 0, 0},
{0, 1, 0},
{1, 1, 0},
{2, 1, 0},
{3, 1, 0},
{4, 1, 0},
{0, 2, 0},
{1, 2, 0},
{2, 2, 0},
{3, 2, 0},
{4, 2, 0},
{0, 3, 0},
{1, 3, 0},
{2, 3, 0},
{3, 3, 0},
{4, 3, 0},
{0, 4, 0},
{1, 4, 0},
{2, 4, 0},
{3, 4, 0},
{4, 4, 0},
{0, 0, 1},
{1, 0, 1},
{2, 0, 1},
{3, 0, 1},
{4, 0, 1},
{0, 1, 1},
{1, 1, 1},
{2, 1, 1},
{3, 1, 1},
{4, 1, 1},
{0, 2, 1},
{1, 2, 1},
{2, 2, 1},
{3, 2, 1},
{4, 2, 1},
{0, 3, 1},
{1, 3, 1},
{2, 3, 1},
{3, 3, 1},
{4, 3, 1},
{0, 4, 1},
{1, 4, 1},
{2, 4, 1},
{3, 4, 1},
{4, 4, 1},
{0, 0, 2},
{1, 0, 2},
{2, 0, 2},
{3, 0, 2},
{4, 0, 2},
{0, 1, 2},
{1, 1, 2},
{2, 1, 2},
{3, 1, 2},
{4, 1, 2},
{0, 2, 2},
{1, 2, 2},
{2, 2, 2},
{3, 2, 2},
{4, 2, 2},
{0, 3, 2},
{1, 3, 2},
{2, 3, 2},
{3, 3, 2},
{4, 3, 2},
{0, 4, 2},
{1, 4, 2},
{2, 4, 2},
{3, 4, 2},
{4, 4, 2},
{0, 0, 3},
{1, 0, 3},
{2, 0, 3},
{3, 0, 3},
{4, 0, 3},
{0, 1, 3},
{1, 1, 3},
{2, 1, 3},
{3, 1, 3},
{4, 1, 3},
{0, 2, 3},
{1, 2, 3},
{2, 2, 3},
{3, 2, 3},
{4, 2, 3},
{0, 3, 3},
{1, 3, 3},
{2, 3, 3},
{3, 3, 3},
{4, 3, 3},
{0, 4, 3},
{1, 4, 3},
{2, 4, 3},
{3, 4, 3},
{4, 4, 3},
{0, 0, 4},
{1, 0, 4},
{2, 0, 4},
{3, 0, 4},
{4, 0, 4},
{0, 1, 4},
{1, 1, 4},
{2, 1, 4},
{3, 1, 4},
{4, 1, 4},
{0, 2, 4},
{1, 2, 4},
{2, 2, 4},
{3, 2, 4},
{4, 2, 4},
{0, 3, 4},
{1, 3, 4},
{2, 3, 4},
{3, 3, 4},
{4, 3, 4},
{0, 4, 4},
{1, 4, 4},
{2, 4, 4},
{3, 4, 4},
{4, 4, 4}
}; 
//1D Array for the Column defines
int OneD_Column_Array[25] = {Column_1, Column_2, Column_3, Column_4, Column_5, Column_6, Column_7, Column_8, Column_9, Column_10, Column_11, Column_12, Column_13, Column_14, Column_15, Column_16, Column_17, Column_18, Column_19, Column_20, Column_21, Column_22, Column_23, Column_24, Column_25};
int One_To_125_Array[125] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
	50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
	100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124};
	
	int Free_Array[125] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
	50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
	75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
	100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124};
	
//2D Array for the Column defines
int Column_Array[5][5] = {  															//y, x
	{Column_1, Column_2, Column_3, Column_4, Column_5},   	//initializers for row indexed by 0
	{Column_6, Column_7, Column_8, Column_9, Column_10},   	//initializers for row indexed by 1
	{Column_11, Column_12, Column_13, Column_14, Column_15},//initializers for row indexed by 2
	{Column_16, Column_17, Column_18, Column_19, Column_20},//initializers for row indexed by 3
	{Column_21, Column_22, Column_23, Column_24, Column_25} //initializers for row indexed by 4
	};
int cube_on_off_array[5][5][5] = {//z, y, x
	{												//level 1 (Bottom)
		{0, 0, 0, 0, 0},   	
		{0, 0, 0, 0, 0},   
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
		{											//level 2
		{0, 0, 0, 0, 0},   	
		{0, 0, 0, 0, 0},   
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
	{												//level 3
		{0, 0, 0, 0, 0},   	
		{0, 0, 0, 0, 0},   
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
	{												//level 4
		{0, 0, 0, 0, 0},   	
		{0, 0, 0, 0, 0},   
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
	{												//level 5 (Top)
		{0, 0, 0, 0, 0},   	
		{0, 0, 0, 0, 0},   
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	}
};	
	
	
//Array for Level defines
int Level_Array[5] = {level_1, level_2, level_3, level_4, level_5};
/*---------------------------------------------------------------------*/
void LEDinit(void)
{
	//GPIOD->MODER    &= ~(3UL << 2*1);//ultrasonic trigger
	//Onboard LEDs
	GPIOD->MODER |=(1UL << 2*green); 
	GPIOD->MODER |=(1UL << 2*blue);
	GPIOD->MODER |=(1UL << 2*red);
	GPIOD->MODER |=(1UL << 2*orange);
	GPIOD->MODER |=(1UL << 2*1);//ultrasonic trigger
	
	GPIOA->MODER    &= ~(3UL << 2*level_1);
	GPIOA->MODER    &= ~(3UL << 2*level_2);
	GPIOA->MODER    &= ~(3UL << 2*level_3);
	GPIOA->MODER    &= ~(3UL << 2*level_4);
	GPIOA->MODER    &= ~(3UL << 2*level_5);
	//Used for ground layers
	GPIOA->MODER |=((1UL << 2*level_1)|
									(1UL << 2*level_2)|
									(1UL << 2*level_3)|
									(1UL << 2*level_4)|
									(1UL << 2*level_5));
	
	GPIOB->MODER    &= ~(3UL << 2*4);//I might be writing to this port in another init function fix it.
	GPIOB->MODER    &= ~(3UL << 2*3);

	//Used for columns
	
	
	GPIOB->MODER |=((1UL << 2*0)|
									(1UL << 2*1)|
									(1UL << 2*2)|
									(1UL << 2*Column_3)|
									(1UL << 2*4)|
									(1UL << 2*5)|
									(1UL << 2*7)|
									(1UL << 2*8)|
									(1UL << 2*11)|
									(1UL << 2*12)|
									(1UL << 2*13)|
									(1UL << 2*14)|
									(1UL << 2*15));
									
	GPIOA->MODER |=(1UL << 2*3);
	
	//Used for columns
	GPIOE->MODER |=((1UL << 2*2)|
									(1UL << 2*4)|
									(1UL << 2*5)|
									(1UL << 2*6)|
									(1UL << 2*7)|
									(1UL << 2*8)|
									(1UL << 2*9)|
									(1UL << 2*10)|
									(1UL << 2*11)|
									(1UL << 2*12)|
									(1UL << 2*13)|
									(1UL << 2*14)|
									(1UL << 2*15));
	
	//Onboard LEDs
	GPIOD->OTYPER &=~(1UL << green);
	GPIOD->OTYPER &=~(1UL << blue);
	GPIOD->OTYPER &=~(1UL << red);
	GPIOD->OTYPER &=~(1UL << orange);
	GPIOD->OTYPER &=~(1UL << 1);//ultrasonic trigger
	
	//Used for ground layers	
	GPIOA->OTYPER |=((1UL << level_1)|
								 	 (1UL << level_2)|
									 (1UL << level_3)|
									 (1UL << level_4)|
									 (1UL << level_5));
									 
	//Used for columns
	GPIOB->OTYPER &=~((1UL << 0)|
										(1UL << 1)|
										(1UL << 2)|
										(1UL << Column_3)|
										(1UL << 4)|
										(1UL << 5)|
										(1UL << 7)|
										(1UL << 8)|
										(1UL << 11)|
										(1UL << 12)|
										(1UL << 13)|
										(1UL << 14)|
										(1UL << 15));
	GPIOA->OTYPER &=~(1UL << 3);
	//Used for columns
	GPIOE->OTYPER &=~((1UL << 2)|
										(1UL << 4)|
										(1UL << 5)|
										(1UL << 6)|
										(1UL << 7)|
										(1UL << 8)|
										(1UL << 9)|
										(1UL << 10)|
										(1UL << 11)|
										(1UL << 12)|
										(1UL << 13)|
										(1UL << 14)|
										(1UL << 15));
	
	GPIOA->OSPEEDR = 0;		//Set output speed 2MHz low speed
	GPIOA->PUPDR = 0;			//Set no pull up and pull down
}
/*---------------------------------------------------------------------*/
void LED_ON(int x) 						//Switches a specified LED on.
{
	GPIOD->ODR |=(1UL << x);
}
/*---------------------------------------------------------------------*/
void LED_OFF(int x)						//Switches a specified LED off.
{
	GPIOD->ODR &=~(1UL << x);
}
/*---------------------------------------------------------------------*/
void ALL_LED_ON(void)					//Turns all onboard LED's on.
{
	LED_ON(green);							//Turns the green LED on
	LED_ON(orange);							//Turns the orange LED on
	LED_ON(red);								//Turns the red LED on
	LED_ON(blue);								//Turns the blue LED on
}
/*---------------------------------------------------------------------*/
void ALL_ONBOARD_LED_OFF(void)			//Turns all onboard LED's off.
{
	GPIOD->ODR &=~(1UL << green);			//Turns the green LED off
	GPIOD->ODR &=~(1UL << orange);		//Turns the orange LED off
	GPIOD->ODR &=~(1UL << red);				//Turns the red LED off
	GPIOD->ODR &=~(1UL << blue);			//Turns the blue LED off
}
/*---------------------------------------------------------------------*/
void sinewave(int time_frame)
{
	int i;
	int j;
	int sin1, sin2, sin3, sin4, sin5;
	
	if(deg>=360){
		deg=0;
	}else{
		deg=deg+1;
	}	
	
sin1=sin(deg*PI/180)*2.499999+2.5;
sin2=sin(deg*PI/180+0.25*PI)*2.499999+2.5;
sin3=sin(deg*PI/180+0.5*PI)*2.499999+2.5;
sin4=sin(deg*PI/180+0.75*PI)*2.499999+2.5;
sin5=sin(deg*PI/180+1*PI)*2.499999+2.5;
	
	for(j=0; j<time_frame; j++)
	{	
		for(i=0; i<10; i++)//1
		{
			layer_control(Level_Array[sin1], Column_1, One_To_Twelve);
			layer_control(Level_Array[sin1], Column_6, One_To_Twelve);
			layer_control(Level_Array[sin1], Column_11, One_To_Twelve);
			layer_control(Level_Array[sin1], Column_16, Thirteen_To_Twenty_Five);
			layer_control(Level_Array[sin1], Column_21, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		
		for(i=0; i<10; i++)//2
		{
			layer_control(Level_Array[sin2], Column_2, One_To_Twelve);
			layer_control(Level_Array[sin2], Column_7, One_To_Twelve);
			layer_control(Level_Array[sin2], Column_12, One_To_Twelve);
			layer_control(Level_Array[sin2], Column_17, Thirteen_To_Twenty_Five);
			layer_control(Level_Array[sin2], Column_22, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		
		for(i=0; i<10; i++)//3
		{
			layer_control(Level_Array[sin3], Column_3, One_To_Twelve);
			layer_control(Level_Array[sin3], Column_8, One_To_Twelve);
			layer_control(Level_Array[sin3], Column_13, Thirteen_To_Twenty_Five);
			layer_control(Level_Array[sin3], Column_18, Thirteen_To_Twenty_Five);
			layer_control(Level_Array[sin3], Column_23, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		
		for(i=0; i<10; i++)//4
		{
			layer_control(Level_Array[sin4], Column_4, One_To_Twelve);
			layer_control(Level_Array[sin4], Column_9, One_To_Twelve);
			layer_control(Level_Array[sin4], Column_14, Thirteen_To_Twenty_Five);
			layer_control(Level_Array[sin4], Column_19, Thirteen_To_Twenty_Five);
			layer_control(Level_Array[sin4], Column_24, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		
		for(i=0; i<10; i++)//5
		{
			layer_control(Level_Array[sin5], Column_5, One_To_Twelve);
			layer_control(Level_Array[sin5], Column_10, One_To_Twelve);
			layer_control(Level_Array[sin5], Column_15, Thirteen_To_Twenty_Five);
			layer_control(Level_Array[sin5], Column_20, Thirteen_To_Twenty_Five);
			layer_control(Level_Array[sin5], Column_25, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
	}
}
/*---------------------------------------------------------------------*/
void Ultrasonic_Move_LED(int cmx, int cmy, int cmz)
{
	int h_ultrasonic;
	
	if(cmx<=3)
	{
		x_ultrasonic=0;
	}else if(cmx>2 && cmx<=4)
	{
		x_ultrasonic=1;
	}else if(cmx>4 && cmx<=6)
	{
		x_ultrasonic=2;
	}else if(cmx>6 && cmx<=8)
	{
		x_ultrasonic=3;
	}else if(cmx>8 && cmx<=10)
	{
		x_ultrasonic=4;
	}
	
	if(cmy<=3)
	{
		y_ultrasonic=0;
	}else if(cmy>2 && cmy<=4)
	{
		y_ultrasonic=1;
	}else if(cmy>4 && cmy<=6)
	{
		y_ultrasonic=2;
	}else if(cmx>6 && cmy<=8)
	{
		y_ultrasonic=3;
	}else if(cmy>8 && cmy<=10)
	{
		y_ultrasonic=4;
	}
	
	if(cmz<=3)
	{
		z_ultrasonic=0;
	}else if(cmz>2 && cmz<=4)
	{
		z_ultrasonic=1;
	}else if(cmz>4&& cmz<=6)
	{
		z_ultrasonic=2;
	}else if(cmz>6 && cmz<=8)
	{
		z_ultrasonic=3;
	}else if(cmz>8 && cmz<=10)
	{
		z_ultrasonic=4;
	}
	
	if((y_ultrasonic>1 && x_ultrasonic>1)||y_ultrasonic>2){
		h_ultrasonic=2;
	}else{
		h_ultrasonic=1;
	}
	Cube_LED (Level_Array[z_ultrasonic], Column_Array[y_ultrasonic][x_ultrasonic], h_ultrasonic);
}
/*---------------------------------------------------------------------*/
void Sphere(int time_frame)
{
	int i;
	
	for(i=0; i<time_frame; i++)//layer 1
	{
		layer_control(level_1, Column_7, One_To_Twelve);
		layer_control(level_1, Column_8, One_To_Twelve);
		layer_control(level_1, Column_9, One_To_Twelve);
		
		layer_control(level_1, Column_12, One_To_Twelve);
		layer_control(level_1, Column_13, Thirteen_To_Twenty_Five);
		layer_control(level_1, Column_14, Thirteen_To_Twenty_Five);
		
		layer_control(level_1, Column_17, Thirteen_To_Twenty_Five);
		layer_control(level_1, Column_18, Thirteen_To_Twenty_Five);
		layer_control(level_1, Column_19, Thirteen_To_Twenty_Five);
	}
	Cube_Off();
	
		for(i=0; i<time_frame; i++)//layer 2
	{
		layer_control(level_2, Column_2, One_To_Twelve);
		layer_control(level_2, Column_3, One_To_Twelve);
		layer_control(level_2, Column_4, One_To_Twelve);
		
		layer_control(level_2, Column_6, One_To_Twelve);
		layer_control(level_2, Column_7, One_To_Twelve);
		layer_control(level_2, Column_8, One_To_Twelve);
		layer_control(level_2, Column_9, One_To_Twelve);
		layer_control(level_2, Column_10, One_To_Twelve);
		
		layer_control(level_2, Column_11, One_To_Twelve);
		layer_control(level_2, Column_12, One_To_Twelve);
		layer_control(level_2, Column_13, Thirteen_To_Twenty_Five);
		layer_control(level_2, Column_14, Thirteen_To_Twenty_Five);
		layer_control(level_2, Column_15, Thirteen_To_Twenty_Five);
		
		layer_control(level_2, Column_16, Thirteen_To_Twenty_Five);
		layer_control(level_2, Column_17, Thirteen_To_Twenty_Five);
		layer_control(level_2, Column_18, Thirteen_To_Twenty_Five);
		layer_control(level_2, Column_19, Thirteen_To_Twenty_Five);
		layer_control(level_2, Column_20, Thirteen_To_Twenty_Five);
		

		layer_control(level_2, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_2, Column_23, Thirteen_To_Twenty_Five);
		layer_control(level_2, Column_24, Thirteen_To_Twenty_Five);
	}
	Cube_Off();
	
	for(i=0; i<time_frame; i++)//layer 3
	{
		layer_control(level_3, Column_2, One_To_Twelve);
		layer_control(level_3, Column_3, One_To_Twelve);
		layer_control(level_3, Column_4, One_To_Twelve);
		
		layer_control(level_3, Column_6, One_To_Twelve);
		layer_control(level_3, Column_7, One_To_Twelve);
		layer_control(level_3, Column_8, One_To_Twelve);
		layer_control(level_3, Column_9, One_To_Twelve);
		layer_control(level_3, Column_10, One_To_Twelve);
		
		layer_control(level_3, Column_11, One_To_Twelve);
		layer_control(level_3, Column_12, One_To_Twelve);
		layer_control(level_3, Column_13, Thirteen_To_Twenty_Five);
		layer_control(level_3, Column_14, Thirteen_To_Twenty_Five);
		layer_control(level_3, Column_15, Thirteen_To_Twenty_Five);
		
		layer_control(level_3, Column_16, Thirteen_To_Twenty_Five);
		layer_control(level_3, Column_17, Thirteen_To_Twenty_Five);
		layer_control(level_3, Column_18, Thirteen_To_Twenty_Five);
		layer_control(level_3, Column_19, Thirteen_To_Twenty_Five);
		layer_control(level_3, Column_20, Thirteen_To_Twenty_Five);
		

		layer_control(level_3, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_3, Column_23, Thirteen_To_Twenty_Five);
		layer_control(level_3, Column_24, Thirteen_To_Twenty_Five);
	}
	Cube_Off();
	
	for(i=0; i<time_frame; i++)//layer 4
	{
		layer_control(level_4, Column_2, One_To_Twelve);
		layer_control(level_4, Column_3, One_To_Twelve);
		layer_control(level_4, Column_4, One_To_Twelve);
		
		layer_control(level_4, Column_6, One_To_Twelve);
		layer_control(level_4, Column_7, One_To_Twelve);
		layer_control(level_4, Column_8, One_To_Twelve);
		layer_control(level_4, Column_9, One_To_Twelve);
		layer_control(level_4, Column_10, One_To_Twelve);
		
		layer_control(level_4, Column_11, One_To_Twelve);
		layer_control(level_4, Column_12, One_To_Twelve);
		layer_control(level_4, Column_13, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_14, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_15, Thirteen_To_Twenty_Five);
		
		layer_control(level_4, Column_16, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_17, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_18, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_19, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_20, Thirteen_To_Twenty_Five);
		

		layer_control(level_4, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_23, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_24, Thirteen_To_Twenty_Five);
	}
	Cube_Off();
	
	for(i=0; i<time_frame; i++)//layer 5
	{
		layer_control(level_5, Column_7, One_To_Twelve);
		layer_control(level_5, Column_8, One_To_Twelve);
		layer_control(level_5, Column_9, One_To_Twelve);
		
		layer_control(level_5, Column_12, One_To_Twelve);
		layer_control(level_5, Column_13, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_14, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_17, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_18, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_19, Thirteen_To_Twenty_Five);
	}
	Cube_Off();
}
/*---------------------------------------------------------------------*/
void ground_level (int level)//switch off by putting 0/any number
{
	//All grounds off
	GPIOA->ODR |=((1UL << 1)|
							  (1UL << 2)|
							  (1UL << 3)|
							  (1UL << 8)|
							  (1UL << 15));
	//Ground level on
	GPIOA->ODR &=~(1UL << level);
}
/*---------merge functions------------------------------------------*/
void LED_column (int column, int Half)//Off by setting Half to 0.
{
	//All columns off
	GPIOB->ODR &=~ ((1UL << 0)|
									(1UL << 1)|
									(1UL << 2)|
									(1UL << 3)|
									(1UL << 5)|
									(1UL << 7)|
									(1UL << 8)|
									(1UL << 11)|
									(1UL << 12)|
									(1UL << 13)|
									(1UL << 14)|
									(1UL << 15));
	
	GPIOE->ODR &=~ ((1UL << 2)|
									(1UL << 4)|
									(1UL << 5)|
									(1UL << 6)|
									(1UL << 7)|
									(1UL << 8)|
									(1UL << 9)|
									(1UL << 10)|
									(1UL << 11)|
									(1UL << 12)|
									(1UL << 13)|
									(1UL << 14)|
									(1UL << 15)); 
	//Colum on
	if(Half==1){
		GPIOB->ODR |=(1UL << column);
	}else if(Half==2){
		GPIOE->ODR |=(1UL << column);
	}
}
/*---------------------------------------------------------------------*/
void Cube_LED (int level, int column, int Half)
{
	//All grounds off
	GPIOA->ODR |=((1UL << level_1)|
							  (1UL << level_2)|
							  (1UL << level_3)|
							  (1UL << level_4)|
							  (1UL << level_5));

	//All columns off
	GPIOB->ODR &=~ ((1UL << 0)|
									(1UL << 1)|
									(1UL << Column_3)|
									(1UL << 4)|
									(1UL << 5)|
									(1UL << 7)|
									(1UL << 8)|
									(1UL << 11)|
									(1UL << 12)|
									(1UL << 13)|
									(1UL << 14)|
									(1UL << 15));
	
	GPIOE->ODR &=~ ((1UL << 2)|
									(1UL << 4)|
									(1UL << 5)|
									(1UL << 6)|
									(1UL << 7)|
									(1UL << 8)|
									(1UL << 9)|
									(1UL << 10)|
									(1UL << 11)|
									(1UL << 12)|
									(1UL << 13)|
									(1UL << 14)|
									(1UL << 15)); 
									
	//Ground level on
	GPIOA->ODR &=~(1UL << level);
	
	//Colum on
	if(Half==1){
		GPIOB->ODR |=(1UL << column);
	}else if(Half==2){
		GPIOE->ODR |=(1UL << column);
	}
}
/*---------------------------------------------------------------------*/
void Cycle_All_LEDs (int delay)
{
	int a;
	int b;
	int c;
	int LED_Half;
	int Level;
	int Column;
		
	for(a=0; a<5;a++)
	{
		for(b=0; b<5; b++)
		{
			for(c=0; c<5; c++)
			{
				if((b>1 && c>1)||b>2){
					LED_Half=2;
				}else{
					LED_Half=1;
				}
				
				//Column=cube_array[a][b][c];
				Column=Column_Array[b][c];
				Level=Level_Array[a];
				//Column=Column_Array[b][c];
				Cube_LED (Level, Column, LED_Half);//Turns on the specified LED
				delay_nms(delay);
			}
		}//End of Grid for loop
	}//End of Level for loop	
}
/*---------------------------------------------------------------------*/
void Cube_Off(void)
{
	//All grounds off
	GPIOA->ODR |=((1UL << level_1)|
							  (1UL << level_2)|
							  (1UL << level_3)|
							  (1UL << level_4)|
							  (1UL << level_5));

	//All columns off
	GPIOB->ODR &=~ ((1UL << 0)|
									(1UL << 1)|
									(1UL << Column_3)|
									(1UL << 4)|
									(1UL << 5)|
									(1UL << 7)|
									(1UL << 8)|
									(1UL << 11)|
									(1UL << 12)|
									(1UL << 13)|
									(1UL << 14)|
									(1UL << 15));
	
	GPIOE->ODR &=~ ((1UL << 2)|
									(1UL << 4)|
									(1UL << 5)|
									(1UL << 6)|
									(1UL << 7)|
									(1UL << 8)|
									(1UL << 9)|
									(1UL << 10)|
									(1UL << 11)|
									(1UL << 12)|
									(1UL << 13)|
									(1UL << 14)|
									(1UL << 15)); 
}
/*---------------------------------------------------------------------*/
void layer_control(int level, int column, int Half)
{									
	//Ground level on
	GPIOA->ODR &=~(1UL << level);
	
	//Colum on
	if(Half==1){
		GPIOB->ODR |=(1UL << column);
	}else if(Half==2){
		GPIOE->ODR |=(1UL << column);
	}
}
/*---------------------------------------------------------------------*/
void Cube_On(void)
{
	int a;
	int b;
	int c;
	int LED_Half;
	int Level;
	int Column;
	
	for(a=0; a<5;a++)
	{
		Level=Level_Array[a];
		GPIOA->ODR &=~(1UL << Level);//Turns the ground layer on
	}//End of Level for loop	
	
	for(b=0; b<5; b++)
	{
		for(c=0; c<5; c++)
		{
			if((b>1 && c>1)||b>2){
				LED_Half=2;
			}else{
				LED_Half=1;
			}
			Column=Column_Array[b][c];
			layer_control(Level, Column, LED_Half);//Turns on the specified LED
		}
	}//End of Grid for loop
}
/*---------------------------------------------------------------------*/
void Edges(int time_frame)//use size to chose which if statent
{
	int i;
	
	for(i=0; i<time_frame; i++)//layer 1
	{
		layer_control(level_1, Column_1, One_To_Twelve);
		layer_control(level_1, Column_2, One_To_Twelve);
		layer_control(level_1, Column_3, One_To_Twelve);
		layer_control(level_1, Column_4, One_To_Twelve);
		layer_control(level_1, Column_5, One_To_Twelve);
		
		layer_control(level_1, Column_6, One_To_Twelve);
		layer_control(level_1, Column_10, One_To_Twelve);
		
		layer_control(level_1, Column_11, One_To_Twelve);
		layer_control(level_1, Column_15, Thirteen_To_Twenty_Five);
		
		layer_control(level_1, Column_16, Thirteen_To_Twenty_Five);
		layer_control(level_1, Column_20, Thirteen_To_Twenty_Five);

		layer_control(level_1, Column_21, Thirteen_To_Twenty_Five);
		layer_control(level_1, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_1, Column_23, Thirteen_To_Twenty_Five);
		layer_control(level_1, Column_24, Thirteen_To_Twenty_Five);
		layer_control(level_1, Column_25, Thirteen_To_Twenty_Five);
	}
	
	Cube_Off();
	
	for(i=0; i<time_frame; i++)//layer 2
	{
		layer_control(level_2, Column_1, One_To_Twelve);
		layer_control(level_2, Column_5, One_To_Twelve);
		layer_control(level_2, Column_21, Thirteen_To_Twenty_Five);
		layer_control(level_2, Column_25, Thirteen_To_Twenty_Five);
	}
	
	Cube_Off();
	
	for(i=0; i<time_frame; i++)//layer 3
	{
		layer_control(level_3, Column_1, One_To_Twelve);
		layer_control(level_3, Column_5, One_To_Twelve);
		layer_control(level_3, Column_21, Thirteen_To_Twenty_Five);
		layer_control(level_3, Column_25, Thirteen_To_Twenty_Five);
	}
	
	Cube_Off();
	
	for(i=0; i<time_frame; i++)//layer 4
	{
		layer_control(level_4, Column_1, One_To_Twelve);
		layer_control(level_4, Column_5, One_To_Twelve);
		layer_control(level_4, Column_21, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_25, Thirteen_To_Twenty_Five);
	}
	
	Cube_Off();
	
	for(i=0; i<time_frame; i++)//layer 5
	{
		layer_control(level_5, Column_1, One_To_Twelve);
		layer_control(level_5, Column_2, One_To_Twelve);
		layer_control(level_5, Column_3, One_To_Twelve);
		layer_control(level_5, Column_4, One_To_Twelve);
		layer_control(level_5, Column_5, One_To_Twelve);
		
		layer_control(level_5, Column_6, One_To_Twelve);
		layer_control(level_5, Column_10, One_To_Twelve);
		
		layer_control(level_5, Column_11, One_To_Twelve);
		layer_control(level_5, Column_15, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_16, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_20, Thirteen_To_Twenty_Five);

		layer_control(level_5, Column_21, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_23, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_25, Thirteen_To_Twenty_Five);
	}
	
	Cube_Off();
}
/*---------------------------------------------------------------------*/
int random_1_to_6(void)
{
	int i;
		while(UserButton()==1)
		{
			delay_nms(150);
			if (UserButton()==1)
			{
				return getRandomNumber();
			}else 
			{
				i=rand()%6+1;
				return i;
			}
		}	
		return 0;
}
/*---------------------------------------------------------------------*/
int getRandomNumber(void)
{
	return 4; //chosen by fair dice roll.
						//guaranteed to be random.
}
/*---------------------------------------------------------------------*/
void Dice(int number, int time_frame)
{
	int frame;						

	if(number==1){
	
	for(frame=0; frame<time_frame; frame++)//Top face 1
	{
		layer_control(level_5, Column_3, One_To_Twelve);
		
		layer_control(level_5, Column_7, One_To_Twelve);
		layer_control(level_5, Column_8, One_To_Twelve);
		
		layer_control(level_5, Column_13, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_18, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_23, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);	
	}

	Cube_Off();
	}else if(number==2){
	
	for(frame=0; frame<time_frame; frame++)//Top face 2
	{
		layer_control(level_5, Column_1, One_To_Twelve);
		layer_control(level_5, Column_2, One_To_Twelve);
		layer_control(level_5, Column_3, One_To_Twelve);
		layer_control(level_5, Column_4, One_To_Twelve);
		
		layer_control(level_5, Column_10, One_To_Twelve);
		
		layer_control(level_5, Column_12, One_To_Twelve);
		layer_control(level_5, Column_13, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_14, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_16, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_21, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_23, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_25, Thirteen_To_Twenty_Five);	
	}
		Cube_Off();
	}
	else if(number==3){
	
	for(frame=0; frame<time_frame; frame++)//Top face 3
	{
		layer_control(level_5, Column_1, One_To_Twelve);
		layer_control(level_5, Column_2, One_To_Twelve);
		layer_control(level_5, Column_3, One_To_Twelve);
		layer_control(level_5, Column_4, One_To_Twelve);
		
		layer_control(level_5, Column_10, One_To_Twelve);
		
		layer_control(level_5, Column_13, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_14, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_20, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_21, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_23, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);	
	}
		Cube_Off();
	}else if(number==4){
		
	for(frame=0; frame<time_frame; frame++)//Top face 4
	{
		layer_control(level_5, Column_1, One_To_Twelve);
		layer_control(level_5, Column_4, One_To_Twelve);
		
		layer_control(level_5, Column_6, One_To_Twelve);
		layer_control(level_5, Column_9, One_To_Twelve);
		
		layer_control(level_5, Column_11, One_To_Twelve);
		layer_control(level_5, Column_14, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_16, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_17, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_18, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_19, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_20, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);	
	}
		Cube_Off();
	}else if(number==5){
	
	for(frame=0; frame<time_frame; frame++)//Top face 5
	{
		layer_control(level_5, Column_1, One_To_Twelve);
		layer_control(level_5, Column_2, One_To_Twelve);
		layer_control(level_5, Column_3, One_To_Twelve);
		layer_control(level_5, Column_4, One_To_Twelve);
		layer_control(level_5, Column_5, One_To_Twelve);
		
		layer_control(level_5, Column_6, One_To_Twelve);
		
		layer_control(level_5, Column_11, One_To_Twelve);
		layer_control(level_5, Column_12, One_To_Twelve);
		layer_control(level_5, Column_13, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_14, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_20, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_21, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_23, Thirteen_To_Twenty_Five);	
		layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);
	}
		Cube_Off();
	}else if(number==6){
	
	for(frame=0; frame<time_frame; frame++)//Top face 6
	{
		layer_control(level_5, Column_2, One_To_Twelve);
		layer_control(level_5, Column_3, One_To_Twelve);
		layer_control(level_5, Column_4, One_To_Twelve);
		layer_control(level_5, Column_5, One_To_Twelve);
		
		layer_control(level_5, Column_6, One_To_Twelve);
		
		layer_control(level_5, Column_11, One_To_Twelve);
		layer_control(level_5, Column_12, One_To_Twelve);
		layer_control(level_5, Column_13, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_14, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_16, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_20, Thirteen_To_Twenty_Five);
		
		layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_23, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);	
	}
		Cube_Off();
	}
}
/*---------------------------------------------------------------------*/
void Cube_3x3x3_Pulsing(int pulse_speed, int range, int offset)//have an input to control the pulseing speed
{
	int i, l, k;

	l = sin(deg4*PI/180)*range+180;
	
	if(deg4>=360){
		deg4=0;
	}else{
		deg4++;
	}	
	
	for(k=0; k<pulse_speed; k++)
	{
		for(i=0; i<l/4; i++)
		{	
			GPIOB->ODR |=(1UL << Column_7);
			GPIOB->ODR |=(1UL << Column_8);
			GPIOB->ODR |=(1UL << Column_9);
			GPIOB->ODR |=(1UL << Column_12);
			GPIOE->ODR |=(1UL << Column_13);
			GPIOE->ODR |=(1UL << Column_14);
			GPIOE->ODR |=(1UL << Column_17);
			GPIOE->ODR |=(1UL << Column_18);
			GPIOE->ODR |=(1UL << Column_19);
			
			GPIOA->ODR &=~(1UL << level_2);//Turns on layer 2 ground
			GPIOA->ODR &=~(1UL << level_3);//Turns on layer 3 ground
			GPIOA->ODR &=~(1UL << level_4);//Turns on layer 4 ground
		}	
		
		for(i=360; i>l; i--)
		{
			Cube_Off();
		}
	}
}
/*---------------------------------------------------------------------*/
void Heartbeat (void)
{
	int i;
	int j;
	for(j=0; j<1000; j++)
	{
		for(i=0; i<5; i++)
		{
			layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_4, Column_21, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_25, Thirteen_To_Twenty_Five);
		}	
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_3, Column_21, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_25, Thirteen_To_Twenty_Five);
		}	
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_2, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_24, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_1, Column_23, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		
		for(i=0; i<1000; i++)
		{
			Cube_Off();
		}
	}
	//Bright heart
	for(j=0; j<3000; j++)
	{
		for(i=0; i<5; i++)
		{
			layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_4, Column_21, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_25, Thirteen_To_Twenty_Five);
		}	
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_3, Column_21, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_25, Thirteen_To_Twenty_Five);
		}	
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_2, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_24, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_1, Column_23, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
	}
	//second beat
		for(j=0; j<300; j++)
	{
		for(i=0; i<5; i++)
		{
			layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_4, Column_21, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_25, Thirteen_To_Twenty_Five);
		}	
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_3, Column_21, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_25, Thirteen_To_Twenty_Five);
		}	
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_2, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_24, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_1, Column_23, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		
		for(i=0; i<1000; i++)
		{
			Cube_Off();
		}
	}
	//Bright heart
	for(j=0; j<3000; j++)
	{
		for(i=0; i<5; i++)
		{
			layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_5, Column_24, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_4, Column_21, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_25, Thirteen_To_Twenty_Five);
		}	
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_3, Column_21, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_25, Thirteen_To_Twenty_Five);
		}	
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_2, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_24, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		for(i=0; i<5; i++)
		{
			layer_control(level_1, Column_23, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
	}
}
/*---------------------------------------------------------------------*/
void Snake_Game(void)//Snake Game
{
	int posx, posy, posz;
	int i, x, y, z, a;

	int	tailx = snake_array[snake_length][0];
	int taily = snake_array[snake_length][1];
	int tailz = snake_array[snake_length][2];
	int to125;
	int index=0;
	int input;



	for(a=1; a<=snake_length; a++)//Loops through the snake length not including the head
	{
		if(snake_controlx==snake_array[a][0] && snake_controly==snake_array[a][1] && snake_controlz==snake_array[a][2])//If the head hits the body
		{
			Cube_On();
			
			delay_nms(1000);
			Game_Over();
			
			while(1)
			{
				delay_nms(1000);
				Score_Front_Facing(snake_length-1);
			}//Loops infinitely here Showing game over
		}
	}
	
	if(snake_direction==forward){//Updates head position
		snake_controly=snake_controly-1;		
	}else if(snake_direction==backward){
		snake_controly=snake_controly+1;
	}else if(snake_direction==left){
		snake_controlx=snake_controlx-1;
	}else if(snake_direction==right){
		snake_controlx=snake_controlx+1;
	}else if(snake_up_down==up){
		snake_controlz=snake_controlz+1;
	}else if(snake_up_down==down){
		snake_controlz=snake_controlz-1;
	}
	
	//Sets Cube limits for movement
	if(snake_controly==5){//y limits
		Face_On(0);
	}else if(snake_controly==-1){
		Face_On(2);
	}
	
	if(snake_controlx==5){//x limits
		Face_On(1);
	}else if(snake_controlx==-1){
		Face_On(3);
	}
	
	if(snake_controlz==5){//z limits
		Face_On(4);
	}else if(snake_controlz==-1){
		Face_On(5);
	}

		if((snake_controlx==food_position[0] && snake_controly==food_position[1] && snake_controlz==food_position[2]) || start_once==0)//If the head hits food
	{
		if(start_once==1){
			snake_length=snake_length+1;//Increases the snake length by 1
			for(x=0; x<3; x++)//Shifts the last elements of the snake array down.
			{
				snake_array[snake_length][x]=snake_array[snake_length-1][x];
			}
		}else{
			start_once=1;
		}
		
		//loop on off array to check for off bits and write the positions to an array
		for(z=0; z<5; z++)//reset food
		{
			for(y=0; y<5; y++)
			{
				for(x=0; x<5; x++)
				{
					if(cube_on_off_array[z][y][x]==0)
					{
						to125=z*25+y*5+x;
						Free_Array[index]=One_To_125_Array[to125];
						index=index+1;
					}
				}
			}
		}
		input = Free_Array[rand()% (index-1)];
		To_Array_125(input, 1);
	}
	
	if(snake_direction !=0 || snake_up_down !=0)//if there is a change in head position then the array is updated.
	{
		//Shifts all the elements of the snake array down.
		for(y=snake_length; y>=0; y--)//array length -1 down up make this variable
		{
			for(x=0; x<3; x++)
			{
				snake_array[y+1][x]=snake_array[y][x];
			}
		}
		//re-right the first elemnts
		snake_array[0][0]=snake_controlx;
		snake_array[0][1]=snake_controly;
		snake_array[0][2]=snake_controlz;
	}
	
	for(i=0; i<=snake_length; i++)//Loops though the snake array
	{
			posx = snake_array[i][0];
			posy = snake_array[i][1];
			posz = snake_array[i][2];
			cube_on_off_array[posz][posy][posx] = 1;	
	}
	
	if(snake_direction !=0 || snake_up_down !=0)//if there is a change in head position then the array is updated.
	{
		cube_on_off_array[tailz][taily][tailx] = 0;	//turns off the tail LED after a move
	}

	Display_Cube_Array_LEDs_Snake(3000);	
}
/*---------------------------------------------------------------------*/
void Spiral (int speed)
{
	int frame;
	int i;
	
	for(i=0; i<speed; i++)//Frame 1
	{
		for(frame=0; frame<10; frame++)//Layer 1
		{
			layer_control(level_1, Column_2, One_To_Twelve);
			layer_control(level_1, Column_10, One_To_Twelve);
			layer_control(level_1, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_1, Column_16, Thirteen_To_Twenty_Five);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 2
		{
			layer_control(level_2, Column_3, One_To_Twelve);
			layer_control(level_2, Column_15, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_11, One_To_Twelve);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 3
		{
			layer_control(level_3, Column_4, One_To_Twelve);
			layer_control(level_3, Column_20, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_6, One_To_Twelve);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 4
		{
			layer_control(level_4, Column_10, One_To_Twelve);
			layer_control(level_4, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_16, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_2, One_To_Twelve);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 5
		{
			layer_control(level_5, Column_15, Thirteen_To_Twenty_Five);
			layer_control(level_5, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_5, Column_11, One_To_Twelve);
			layer_control(level_5, Column_3, One_To_Twelve);
		}
		Cube_Off();
	}
	
	for(i=0; i<speed; i++)//frame 2
	{
		for(frame=0; frame<10; frame++)//Layer 1
		{
			layer_control(level_1, Column_3, One_To_Twelve);
			layer_control(level_1, Column_15, Thirteen_To_Twenty_Five);
			layer_control(level_1, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_1, Column_11, One_To_Twelve);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 2
		{
			layer_control(level_2, Column_4, One_To_Twelve);
			layer_control(level_2, Column_20, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_6, One_To_Twelve);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 3
		{
			layer_control(level_3, Column_10, One_To_Twelve);
			layer_control(level_3, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_16, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_2, One_To_Twelve);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 4
		{
			layer_control(level_4, Column_15, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_11, One_To_Twelve);
			layer_control(level_4, Column_3, One_To_Twelve);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 5
		{
			layer_control(level_5, Column_4, One_To_Twelve);
			layer_control(level_5, Column_20, Thirteen_To_Twenty_Five);
			layer_control(level_5, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_5, Column_6, One_To_Twelve);
		}
		Cube_Off();
		
	}
	
	for(i=0; i<speed; i++)//frame 3
	{
		for(frame=0; frame<10; frame++)//Layer 1
		{
			layer_control(level_1, Column_4, One_To_Twelve);
			layer_control(level_1, Column_20, Thirteen_To_Twenty_Five);
			layer_control(level_1, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_1, Column_6, One_To_Twelve);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 1
		{
			layer_control(level_2, Column_10, One_To_Twelve);
			layer_control(level_2, Column_24, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_16, Thirteen_To_Twenty_Five);
			layer_control(level_2, Column_2, One_To_Twelve);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 3
		{
			layer_control(level_3, Column_15, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_23, Thirteen_To_Twenty_Five);
			layer_control(level_3, Column_11, One_To_Twelve);
			layer_control(level_3, Column_3, One_To_Twelve);
		}
		Cube_Off();
		
		for(frame=0; frame<10; frame++)//Layer 4
		{
			layer_control(level_4, Column_4, One_To_Twelve);
			layer_control(level_4, Column_20, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_22, Thirteen_To_Twenty_Five);
			layer_control(level_4, Column_6, One_To_Twelve);
		}
		Cube_Off();
		
				for(frame=0; frame<10; frame++)//Layer 5
		{
			layer_control(level_5, Column_10, One_To_Twelve);
			layer_control(level_5, Column_20, Thirteen_To_Twenty_Five);
			layer_control(level_5, Column_16, Thirteen_To_Twenty_Five);
			layer_control(level_5, Column_6, One_To_Twelve);
		}
		Cube_Off();
		
	}
}
/*---------------------------------------------------------------------*/
void Cube_Double_sine(int speed)
{
	int i;
	int j;
	int k;
	
	int sin1, sin2, sin3, sin4, sin5, sin6, sin7, sin8, sin9, sin10, sin11, sin12, sin13, sin14, sin15, sin16;
	
	if(deg3>=360){
		deg3=0;
	}else{
		deg3=deg3+1;
	}	
	
sin1=sin(deg3*PI/180)*2.499999+2.5;//22.5
sin2=sin(deg3*PI/180+45*PI/180)*2.499999+2.5;
sin3=sin(deg3*PI/180+2*45*PI/180)*2.499999+2.5;
sin4=sin(deg3*PI/180+3*45*PI/180)*2.499999+2.5;
sin5=sin(deg3*PI/180+4*45*PI/180)*2.499999+2.5;
sin6=sin(deg3*PI/180+5*45*PI/180)*2.499999+2.5;
sin7=sin(deg3*PI/180+6*45*PI/180)*2.499999+2.5;
sin8=sin(deg3*PI/180+7*45*PI/180)*2.499999+2.5;
sin9=sin(deg3*PI/180+8*45*PI/180)*2.499999+2.5;
sin10=sin(deg3*PI/180+9*45*PI/180)*2.499999+2.5;
sin11=sin(deg3*PI/180+10*45*PI/180)*2.499999+2.5;
sin12=sin(deg3*PI/180+11*45*PI/180)*2.499999+2.5;
sin13=sin(deg3*PI/180+12*45*PI/180)*2.499999+2.5;
sin14=sin(deg3*PI/180+13*45*PI/180)*2.499999+2.5;
sin15=sin(deg3*PI/180+14*45*PI/180)*2.499999+2.5;
sin16=sin(deg3*PI/180+15*45*PI/180)*2.499999+2.5;

//loop array if sinx==ground array level
			layer_control(Level_Array[sin1], Column_11, One_To_Twelve);
			layer_control(Level_Array[sin1], Column_16, Thirteen_To_Twenty_Five);
	
	for(j=0; j<speed; j++)
	{	
		for(i=0; i<=4; i++)
		{
			for(k=0; k<10; k++)
			{
				if(sin1==i)
				{
					layer_control(Level_Array[sin1], Column_1, One_To_Twelve);
				}
				if(sin2==i)
				{
					layer_control(Level_Array[sin2], Column_2, One_To_Twelve);
				}
				if(sin3==i)
				{
					layer_control(Level_Array[sin3], Column_3, One_To_Twelve);
				}
				if(sin4==i)
				{
					layer_control(Level_Array[sin4], Column_4, One_To_Twelve);
				}
				if(sin5==i)
				{
					layer_control(Level_Array[sin5], Column_5, One_To_Twelve);
				}
				if(sin6==i)
				{
					layer_control(Level_Array[sin6], Column_10, One_To_Twelve);
				}
				if(sin7==i)
				{
					layer_control(Level_Array[sin7], Column_15, Thirteen_To_Twenty_Five);
				}
				if(sin8==i)
				{
					layer_control(Level_Array[sin8], Column_20, Thirteen_To_Twenty_Five);
				}
				if(sin9==i)
				{
					layer_control(Level_Array[sin9], Column_25, Thirteen_To_Twenty_Five);
				}
				if(sin10==i)
				{
					layer_control(Level_Array[sin10], Column_24, Thirteen_To_Twenty_Five);
				}
				if(sin11==i)
				{
					layer_control(Level_Array[sin11], Column_23, Thirteen_To_Twenty_Five);
				}
				if(sin12==i)
				{
					layer_control(Level_Array[sin12], Column_22, Thirteen_To_Twenty_Five);
				}
				if(sin13==i)
				{
					layer_control(Level_Array[sin13], Column_21, Thirteen_To_Twenty_Five);
				}
				if(sin14==i)
				{
					layer_control(Level_Array[sin14], Column_16, Thirteen_To_Twenty_Five);
				}
				if(sin15==i)
				{
					layer_control(Level_Array[sin15], Column_11, One_To_Twelve);
				}
				if(sin16==i)
				{
					layer_control(Level_Array[sin16], Column_6, One_To_Twelve);
				}
			}
			Cube_Off();
		}
	}
}
/*---------------------------------------------------------------------*/
void Cube_sine(int speed)
{
	int i;
	int j;
	int k;
	
	int sin1, sin2, sin3, sin4, sin5, sin6, sin7, sin8, sin9, sin10, sin11, sin12, sin13, sin14, sin15, sin16;
	
	if(deg2>=360){
		deg2=0;
	}else{
		deg2=deg2+1;
	}	

//Notice me Sin PI
sin1=sin(deg2*PI/180)*2.499999+2.5;//22.5
sin2=sin(deg2*PI/180+22.5*PI/180)*2.499999+2.5;
sin3=sin(deg2*PI/180+2*22.5*PI/180)*2.499999+2.5;
sin4=sin(deg2*PI/180+3*22.5*PI/180)*2.499999+2.5;
sin5=sin(deg2*PI/180+4*22.5*PI/180)*2.499999+2.5;
sin6=sin(deg2*PI/180+5*22.5*PI/180)*2.499999+2.5;
sin7=sin(deg2*PI/180+6*22.5*PI/180)*2.499999+2.5;
sin8=sin(deg2*PI/180+7*22.5*PI/180)*2.499999+2.5;
sin9=sin(deg2*PI/180+8*22.5*PI/180)*2.499999+2.5;
sin10=sin(deg2*PI/180+9*22.5*PI/180)*2.499999+2.5;
sin11=sin(deg2*PI/180+10*22.5*PI/180)*2.499999+2.5;
sin12=sin(deg2*PI/180+11*22.5*PI/180)*2.499999+2.5;
sin13=sin(deg2*PI/180+12*22.5*PI/180)*2.499999+2.5;
sin14=sin(deg2*PI/180+13*22.5*PI/180)*2.499999+2.5;
sin15=sin(deg2*PI/180+14*22.5*PI/180)*2.499999+2.5;
sin16=sin(deg2*PI/180+15*22.5*PI/180)*2.499999+2.5;

//loop array if sinx==ground array level
			layer_control(Level_Array[sin1], Column_11, One_To_Twelve);
			layer_control(Level_Array[sin1], Column_16, Thirteen_To_Twenty_Five);
	
	for(j=0; j<speed; j++)
	{	
		for(i=0; i<=4; i++)
		{
			for(k=0; k<10; k++)
			{
				if(sin1==i)
				{
					layer_control(Level_Array[sin1], Column_1, One_To_Twelve);
				}
				if(sin2==i)
				{
					layer_control(Level_Array[sin2], Column_2, One_To_Twelve);
				}
				if(sin3==i)
				{
					layer_control(Level_Array[sin3], Column_3, One_To_Twelve);
				}
				if(sin4==i)
				{
					layer_control(Level_Array[sin4], Column_4, One_To_Twelve);
				}
				if(sin5==i)
				{
					layer_control(Level_Array[sin5], Column_5, One_To_Twelve);
				}
				if(sin6==i)
				{
					layer_control(Level_Array[sin6], Column_10, One_To_Twelve);
				}
				if(sin7==i)
				{
					layer_control(Level_Array[sin7], Column_15, Thirteen_To_Twenty_Five);
				}
				if(sin8==i)
				{
					layer_control(Level_Array[sin8], Column_20, Thirteen_To_Twenty_Five);
				}
				if(sin9==i)
				{
					layer_control(Level_Array[sin9], Column_25, Thirteen_To_Twenty_Five);
				}
				if(sin10==i)
				{
					layer_control(Level_Array[sin10], Column_24, Thirteen_To_Twenty_Five);
				}
				if(sin11==i)
				{
					layer_control(Level_Array[sin11], Column_23, Thirteen_To_Twenty_Five);
				}
				if(sin12==i)
				{
					layer_control(Level_Array[sin12], Column_22, Thirteen_To_Twenty_Five);
				}
				if(sin13==i)
				{
					layer_control(Level_Array[sin13], Column_21, Thirteen_To_Twenty_Five);
				}
				if(sin14==i)
				{
					layer_control(Level_Array[sin14], Column_16, Thirteen_To_Twenty_Five);
				}
				if(sin15==i)
				{
					layer_control(Level_Array[sin15], Column_11, One_To_Twelve);
				}
				if(sin16==i)
				{
					layer_control(Level_Array[sin16], Column_6, One_To_Twelve);
				}
			}
			Cube_Off();
		}
	}
}
/*---------------------------------------------------------------------*/
void Analogue_LED(void)
{
	int i;
	int l;
	int LED_Half;
	int direction=analogue_direction_1();
	int up_down=analogue_direction_2();
	
	if(direction==forward){
		analoguey=analoguey-1;
	}else if(direction==backward){
		analoguey=analoguey+1;
	}else if(direction==left){
		analoguex=analoguex-1;
	}else if(direction==right){
		analoguex=analoguex+1;
	}
	
	if(up_down==up){
		analogue_level=analogue_level+1;
	}else if(up_down==down){
		analogue_level=analogue_level-1;
	}
	
	if(analoguey==5){
		analoguey=4;
	}else if(analoguey==-1){
		analoguey=0;
	}
	
	if(analoguex==5){
		analoguex=4;
	}else if(analoguex==-1){
		analoguex=0;
	}
	
	if(analogue_level==5){
		analogue_level=4;
	}else if(analogue_level==-1){
		analogue_level=0;
	}
	
	i=Column_Array[analoguey][analoguex];
	l=Level_Array[analogue_level];
	
	if((analoguey>1 && analoguex>1)||analoguey>2){
		LED_Half=2;
	}else{
		LED_Half=1;
	}
	
	Cube_LED (l, i, LED_Half);
}
/*---------------------------------------------------------------------*/
void Random_LED(int delay)
{
	int Random_LED_level;
	int Random_LED_column;
	int LED_Half;	
	int x, y, z;
	
	x=rand()%5;
	y=rand()%5;
	z=rand()%5;
	
	Random_LED_column=Column_Array[y][x];
	Random_LED_level=Level_Array[z];
	
	if((y>1 && x>1)||y>2){
		LED_Half=2;
	}else{
		LED_Half=1;
	}
	
	Cube_LED(Random_LED_level, Random_LED_column, LED_Half);
	delay_nms(delay);
}
/*---------------------------------------------------------------------*/
void Cube_Array_LEDs(int x, int y, int z, int On_Off)
{
	cube_on_off_array[z][y][x] = On_Off;	
}
/*---------------------------------------------------------------------*/
void Reset_Cube_Array_LEDs(void)
{
	int x, y, z; //Ints used for the for loops
	
	for(z=0; z<5; z++)
	{
		for(y=0; y<5; y++)
		{
			for(x=0; x<5; x++)
			{
				cube_on_off_array[z][y][x] = 0;	
			}
		}
	}
}
/*---------------------------------------------------------------------*/
void Display_Cube_Array_LEDs_Snake(int speed)
{
	int x, y, z, i, j; //variables used fro for loops
	int LED;
	int LED_Half;
	int Column;
	int level;
	int s, s2, opposite=0;
	
	for(i=0; i<speed; i++)
	{
	s = analogue_direction_1();
	s2 = analogue_direction_2();
	
		if((snake_up_down==down && s2==up)||(snake_up_down==up && s2==down)||(snake_direction==backward && s==forward)||(snake_direction==forward && s==backward) || (snake_direction==right && s==left)||(snake_direction==left && s==right)||(first_move==0 && s==backward))
		{
			opposite=1;
		}
		
		if((s != 0 || s2 !=0) && opposite==0)
		{
			s3=s;
			s4=s2;
		}
		
		for(z=0; z<5; z++)
		{
			for(j=0; j<3; j++)
			{
				for(y=0; y<5; y++)
				{
					for(x=0; x<5; x++)
					{
						LED = cube_on_off_array[z][y][x];
						Column = Column_Array[y][x];
						level = Level_Array[z];
						
						if((y>1 && x>1)||y>2){
							LED_Half=2;
						}else{
							LED_Half=1;
						}
						
						if(LED==1){
							layer_control(level, Column, LED_Half);
						}
					}
				}
			}
			Cube_Off();
		}
	}

	snake_direction=s3;
	snake_up_down=s4;
	
	if(snake_direction !=0 || snake_up_down !=0)
	{
		first_move=1;
	}
	
}
/*---------------------------------------------------------------------*/
void Non_Repeating_Random_LEDs (int On_Off)
{
	int random;
	int rand_lim=125;
	int q, w, e;
	int random_element;
	for(rand_lim=125; rand_lim>0; rand_lim--)
	{
		random = rand() % rand_lim;
		random_element=One_To_125_Array[random];

		for(q=random; q<124; q++)//Shifts the array to the left
		{
			One_To_125_Array[q] = One_To_125_Array[q+1];
		}
		One_To_125_Array[124] = random_element;//Writes the random number in last space in the array.
	}
	
	for(w=0; w<125; w++)
	{	
		e = One_To_125_Array[w];	

		To_Array_125(e, On_Off);
		Display_Cube_Array_LEDs_Snake(300);
	}
	//Reset_Cube_Array_LEDs();
}
/*---------------------------------------------------------------------*/
void To_Array_125(int input, int On_Off)
{
	int x, y ,z;
	
	if(input<25){
		z=0;
	}else if(input<50){
		z=1;
		input = input -25;
	}else if(input<75){
		z=2;
		input = input -50;
	}else if(input<100){
		z=3;
		input = input -75;
	}else if(input<125){
		z=4;
		input = input -100;
	}
	
	if(input<5){
		y=0;
	}else if(input<10){
		y=1;
		input = input -5;
	}else if(input<15){
		y=2;
		input = input -10;
	}else if(input<20){
		y=3;
		input = input -15;
	}else if(input<25){
		y=4;
		input = input -20;
	}

	x=input;
	
	food_position[0] = x;
	food_position[1] = y;
	food_position[2] = z;
	
	cube_on_off_array[z][y][x] = On_Off;	
}
/*---------------------------------------------------------------------*/
void Face_On(int face)
{
	int x, y;
	int LED_Half;
	int Column;
	
	if(face==0){
		layer_control(level_1, Column_21, Thirteen_To_Twenty_Five);
		layer_control(level_2, Column_22, Thirteen_To_Twenty_Five);
		layer_control(level_3, Column_23, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_24, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_25, Thirteen_To_Twenty_Five);
	}else if(face==1){
		layer_control(level_1, Column_5, One_To_Twelve);
		layer_control(level_2, Column_10, One_To_Twelve);
		layer_control(level_3, Column_15, Thirteen_To_Twenty_Five);
		layer_control(level_4, Column_20, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_25, Thirteen_To_Twenty_Five);
	}else if(face==2){
		layer_control(level_1, Column_1, One_To_Twelve);
		layer_control(level_2, Column_2, One_To_Twelve);
		layer_control(level_3, Column_3, One_To_Twelve);
		layer_control(level_4, Column_4, One_To_Twelve);
		layer_control(level_5, Column_5, One_To_Twelve);
	}else if(face==3){
		layer_control(level_1, Column_1, One_To_Twelve);
		layer_control(level_2, Column_6, One_To_Twelve);
		layer_control(level_3, Column_11, One_To_Twelve);
		layer_control(level_4, Column_16, Thirteen_To_Twenty_Five);
		layer_control(level_5, Column_21, Thirteen_To_Twenty_Five);
	}else if(face==4){
		for(y=0; y<5; y++)
		{
			for(x=0; x<5; x++)
			{
				if((y>1 && x>1)||y>2){
					LED_Half=2;
				}else{
					LED_Half=1;
				}
				Column = Column_Array[y][x];
				layer_control(level_5, Column, LED_Half);//Turns on the specified LED
			}
		}
	}else if(face==5){
		for(y=0; y<5; y++)
		{
			for(x=0; x<5; x++)
			{
				if((y>1 && x>1)||y>2){
					LED_Half=2;
				}else{
					LED_Half=1;
				}
				Column = Column_Array[y][x];
				layer_control(level_1, Column, LED_Half);//Turns on the specified LED
			}
		}
	}
	delay_nms(1000);
	Game_Over();
	
	while(1)
	{
		delay_nms(1000);
		Score_Front_Facing(snake_length-1);
	}//Loops infinitely here Showing game over
}

void Rain(int speed)
{
	int x, y, z;
	for(z=0; z<5; z++)
	{
		for(x=0; x<5; x++)
		{
			for(y=0; y<5; y++)
			{
				if(z==4)
				{
					for(x=0; x<5; x++)//Clears top layer
					{
						for(y=0; y<5; y++)
						{
							cube_on_off_array[4][y][x] = 0;
						}
					}
				}else{
					cube_on_off_array[z][y][x] = cube_on_off_array[z+1][y][x];
				}
			}
		}
}
	cube_on_off_array[4][rand() % 5][rand() % 5] = 1; //Layer 5
	Display_Cube_Array_LEDs(speed);//Displays the LED array
}

//void Rain(int time_frame)//number of times it loops to increase time use about 30000
//{
//	int frame;						//30 frames should be needed
//												//conect last and first frames
//	for(frame=0; frame<time_frame; frame++)//frame 1
//	{
//		Cube_LED(level_5, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_8, One_To_Twelve);
//		Cube_LED(level_3, Column_12, One_To_Twelve);
//		Cube_LED(level_2, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_3, One_To_Twelve);		
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 2
//	{
//		Cube_LED(level_5, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_8, One_To_Twelve);
//		Cube_LED(level_2, Column_12, One_To_Twelve);
//		Cube_LED(level_1, Column_13, Thirteen_To_Twenty_Five);		
//	}

//	for(frame=0; frame<time_frame; frame++)//frame 3
//	{
//		Cube_LED(level_5, Column_2, One_To_Twelve);
//		Cube_LED(level_4, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_8, One_To_Twelve);
//		Cube_LED(level_1, Column_12, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 4
//	{
//		Cube_LED(level_5, Column_6, One_To_Twelve);
//		Cube_LED(level_4, Column_2, One_To_Twelve);
//		Cube_LED(level_3, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_8, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 5
//	{
//		Cube_LED(level_5, Column_10, One_To_Twelve);
//		Cube_LED(level_4, Column_6, One_To_Twelve);
//		Cube_LED(level_3, Column_2, One_To_Twelve);
//		Cube_LED(level_2, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_19, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 6
//	{
//		Cube_LED(level_5, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_10, One_To_Twelve);
//		Cube_LED(level_3, Column_6, One_To_Twelve);
//		Cube_LED(level_2, Column_2, One_To_Twelve);
//		Cube_LED(level_1, Column_24, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 7
//	{
//		Cube_LED(level_5, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_10, One_To_Twelve);
//		Cube_LED(level_2, Column_6, One_To_Twelve);
//		Cube_LED(level_1, Column_2, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 8
//	{
//		Cube_LED(level_5, Column_7, One_To_Twelve);
//		Cube_LED(level_4, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_10, One_To_Twelve);
//		Cube_LED(level_1, Column_6, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 9
//	{
//		Cube_LED(level_5, Column_9, One_To_Twelve);
//		Cube_LED(level_4, Column_7, One_To_Twelve);
//		Cube_LED(level_3, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_10, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 10
//	{
//		Cube_LED(level_5, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_9, One_To_Twelve);
//		Cube_LED(level_3, Column_7, One_To_Twelve);
//		Cube_LED(level_2, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_17, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 11
//	{
//		Cube_LED(level_5, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_9, One_To_Twelve);
//		Cube_LED(level_2, Column_7, One_To_Twelve);
//		Cube_LED(level_1, Column_20, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 12
//	{
//		Cube_LED(level_5, Column_4, One_To_Twelve);
//		Cube_LED(level_4, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_9, One_To_Twelve);
//		Cube_LED(level_1, Column_7, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 13
//	{
//		Cube_LED(level_5, Column_11, One_To_Twelve);
//		Cube_LED(level_4, Column_4, One_To_Twelve);
//		Cube_LED(level_3, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_9, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 14
//	{
//		Cube_LED(level_5, Column_5, One_To_Twelve);
//		Cube_LED(level_4, Column_11, One_To_Twelve);
//		Cube_LED(level_3, Column_4, One_To_Twelve);
//		Cube_LED(level_2, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_18, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 15
//	{
//		Cube_LED(level_5, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_5, One_To_Twelve);
//		Cube_LED(level_3, Column_11, One_To_Twelve);
//		Cube_LED(level_2, Column_4, One_To_Twelve);
//		Cube_LED(level_1, Column_14, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 16
//	{
//		Cube_LED(level_5, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_5, One_To_Twelve);
//		Cube_LED(level_2, Column_11, One_To_Twelve);
//		Cube_LED(level_1, Column_4, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 17
//	{
//		Cube_LED(level_5, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_5, One_To_Twelve);
//		Cube_LED(level_1, Column_11, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 18
//	{
//		Cube_LED(level_5, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_5, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 19
//	{
//		Cube_LED(level_5, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_15, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 20
//	{
//		Cube_LED(level_5, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_22, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 21
//	{
//		Cube_LED(level_5, Column_1, One_To_Twelve);
//		Cube_LED(level_4, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_25, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 22
//	{
//		Cube_LED(level_5, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_1, One_To_Twelve);
//		Cube_LED(level_3, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_23, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 23
//	{
//		Cube_LED(level_5, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_1, One_To_Twelve);
//		Cube_LED(level_2, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_16, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 24
//	{
//		Cube_LED(level_5, Column_1, One_To_Twelve);
//		Cube_LED(level_4, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_1, One_To_Twelve);
//		Cube_LED(level_1, Column_21, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 25
//	{
//		Cube_LED(level_5, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_1, One_To_Twelve);
//		Cube_LED(level_3, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_1, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 26
//	{
//		Cube_LED(level_5, Column_10, One_To_Twelve);
//		Cube_LED(level_4, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_1, One_To_Twelve);
//		Cube_LED(level_2, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_23, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 27
//	{
//		Cube_LED(level_5, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_10, One_To_Twelve);
//		Cube_LED(level_3, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_1, One_To_Twelve);
//		Cube_LED(level_1, Column_19, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 28
//	{
//		Cube_LED(level_5, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_10, One_To_Twelve);
//		Cube_LED(level_2, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_1, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 29
//	{
//		Cube_LED(level_5, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_10, One_To_Twelve);
//		Cube_LED(level_1, Column_18, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 30
//	{
//		Cube_LED(level_5, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_10, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 31
//	{
//		Cube_LED(level_5, Column_6, One_To_Twelve);
//		Cube_LED(level_4, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_24, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 32
//	{
//		Cube_LED(level_5, Column_4, One_To_Twelve);
//		Cube_LED(level_4, Column_6, One_To_Twelve);
//		Cube_LED(level_3, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_25, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 33
//	{
//		Cube_LED(level_5, Column_3, One_To_Twelve);
//		Cube_LED(level_4, Column_4, One_To_Twelve);
//		Cube_LED(level_3, Column_6, One_To_Twelve);
//		Cube_LED(level_2, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_13, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 34
//	{
//		Cube_LED(level_5, Column_5, One_To_Twelve);
//		Cube_LED(level_4, Column_3, One_To_Twelve);
//		Cube_LED(level_3, Column_4, One_To_Twelve);
//		Cube_LED(level_2, Column_6, One_To_Twelve);
//		Cube_LED(level_1, Column_20, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 35
//	{
//		Cube_LED(level_5, Column_7, One_To_Twelve);
//		Cube_LED(level_4, Column_5, One_To_Twelve);
//		Cube_LED(level_3, Column_3, One_To_Twelve);
//		Cube_LED(level_2, Column_4, One_To_Twelve);
//		Cube_LED(level_1, Column_6, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 36
//	{
//		Cube_LED(level_5, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_7, One_To_Twelve);
//		Cube_LED(level_3, Column_5, One_To_Twelve);
//		Cube_LED(level_2, Column_3, One_To_Twelve);
//		Cube_LED(level_1, Column_4, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 37
//	{
//		Cube_LED(level_5, Column_9, One_To_Twelve);
//		Cube_LED(level_4, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_7, One_To_Twelve);
//		Cube_LED(level_2, Column_5, One_To_Twelve);
//		Cube_LED(level_1, Column_3, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 38
//	{
//		Cube_LED(level_5, Column_8, One_To_Twelve);
//		Cube_LED(level_4, Column_9, One_To_Twelve);
//		Cube_LED(level_3, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_7, One_To_Twelve);
//		Cube_LED(level_1, Column_5, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 39
//	{
//		Cube_LED(level_5, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_8, One_To_Twelve);
//		Cube_LED(level_3, Column_9, One_To_Twelve);
//		Cube_LED(level_2, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_7, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 40
//	{
//		Cube_LED(level_5, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_8, One_To_Twelve);
//		Cube_LED(level_2, Column_9, One_To_Twelve);
//		Cube_LED(level_1, Column_21, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 41
//	{
//		Cube_LED(level_5, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_8, One_To_Twelve);
//		Cube_LED(level_1, Column_9, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 42
//	{
//		Cube_LED(level_5, Column_12, One_To_Twelve);
//		Cube_LED(level_4, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_8, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 43
//	{
//		Cube_LED(level_5, Column_11, One_To_Twelve);
//		Cube_LED(level_4, Column_12, One_To_Twelve);
//		Cube_LED(level_3, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_17, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 44
//	{
//		Cube_LED(level_5, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_11, One_To_Twelve);
//		Cube_LED(level_3, Column_12, One_To_Twelve);
//		Cube_LED(level_2, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_22, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 45
//	{
//		Cube_LED(level_5, Column_2, One_To_Twelve);
//		Cube_LED(level_4, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_11, One_To_Twelve);
//		Cube_LED(level_2, Column_12, One_To_Twelve);
//		Cube_LED(level_1, Column_15, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 46
//	{
//		Cube_LED(level_5, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_2, One_To_Twelve);
//		Cube_LED(level_3, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_11, One_To_Twelve);
//		Cube_LED(level_1, Column_12, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 47
//	{
//		Cube_LED(level_5, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_2, One_To_Twelve);
//		Cube_LED(level_2, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_11, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 48
//	{
//		Cube_LED(level_5, Column_1, One_To_Twelve);
//		Cube_LED(level_4, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_2, One_To_Twelve);
//		Cube_LED(level_1, Column_16, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 49
//	{
//		Cube_LED(level_5, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_1, One_To_Twelve);
//		Cube_LED(level_3, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_2, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 50
//	{
//		Cube_LED(level_5, Column_2, One_To_Twelve);
//		Cube_LED(level_4, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_1, One_To_Twelve);
//		Cube_LED(level_2, Column_15, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_14, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 51
//	{
//		Cube_LED(level_5, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_2, One_To_Twelve);
//		Cube_LED(level_3, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_1, One_To_Twelve);
//		Cube_LED(level_1, Column_15, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 52
//	{
//		Cube_LED(level_5, Column_5, One_To_Twelve);
//		Cube_LED(level_4, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_2, One_To_Twelve);
//		Cube_LED(level_2, Column_20, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_1, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 53
//	{
//		Cube_LED(level_5, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_5, One_To_Twelve);
//		Cube_LED(level_3, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_2, One_To_Twelve);
//		Cube_LED(level_1, Column_20, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 54
//	{
//		Cube_LED(level_5, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_5, One_To_Twelve);
//		Cube_LED(level_2, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_2, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 55
//	{
//		Cube_LED(level_5, Column_12, One_To_Twelve);
//		Cube_LED(level_4, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_5, One_To_Twelve);
//		Cube_LED(level_1, Column_13, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 56
//	{
//		Cube_LED(level_5, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_12, One_To_Twelve);
//		Cube_LED(level_3, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_17, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_5, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 57
//	{
//		Cube_LED(level_5, Column_7, One_To_Twelve);
//		Cube_LED(level_4, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_12, One_To_Twelve);
//		Cube_LED(level_2, Column_14, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_17, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 58
//	{
//		Cube_LED(level_5, Column_4, One_To_Twelve);
//		Cube_LED(level_4, Column_7, One_To_Twelve);
//		Cube_LED(level_3, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_12, One_To_Twelve);
//		Cube_LED(level_1, Column_14, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 59
//	{
//		Cube_LED(level_5, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_4, One_To_Twelve);
//		Cube_LED(level_3, Column_7, One_To_Twelve);
//		Cube_LED(level_2, Column_24, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_12, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 60
//	{
//		Cube_LED(level_5, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_4, One_To_Twelve);
//		Cube_LED(level_2, Column_7, One_To_Twelve);
//		Cube_LED(level_1, Column_24, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 61
//	{
//		Cube_LED(level_5, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_4, One_To_Twelve);
//		Cube_LED(level_1, Column_7, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 62
//	{
//		Cube_LED(level_5, Column_6, One_To_Twelve);
//		Cube_LED(level_4, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_25, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_4, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 63
//	{
//		Cube_LED(level_5, Column_9, One_To_Twelve);
//		Cube_LED(level_4, Column_6, One_To_Twelve);
//		Cube_LED(level_3, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_23, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_25, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 64
//	{
//		Cube_LED(level_5, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_9, One_To_Twelve);
//		Cube_LED(level_3, Column_6, One_To_Twelve);
//		Cube_LED(level_2, Column_16, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_23, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 65
//	{
//		Cube_LED(level_5, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_9, One_To_Twelve);
//		Cube_LED(level_2, Column_6, One_To_Twelve);
//		Cube_LED(level_1, Column_16, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 66
//	{
//		Cube_LED(level_5, Column_8, One_To_Twelve);
//		Cube_LED(level_4, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_9, One_To_Twelve);
//		Cube_LED(level_1, Column_6, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 67
//	{
//		Cube_LED(level_5, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_8, One_To_Twelve);
//		Cube_LED(level_3, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_19, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_9, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 68
//	{
//		Cube_LED(level_5, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_8, One_To_Twelve);
//		Cube_LED(level_2, Column_22, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_19, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 69
//	{
//		Cube_LED(level_5, Column_11, One_To_Twelve);
//		Cube_LED(level_4, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_8, One_To_Twelve);
//		Cube_LED(level_1, Column_22, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 70
//	{
//		Cube_LED(level_5, Column_3, One_To_Twelve);
//		Cube_LED(level_4, Column_11, One_To_Twelve);
//		Cube_LED(level_3, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_21, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_8, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 71
//	{
//		Cube_LED(level_5, Column_10, One_To_Twelve);
//		Cube_LED(level_4, Column_3, One_To_Twelve);
//		Cube_LED(level_3, Column_11, One_To_Twelve);
//		Cube_LED(level_2, Column_18, Thirteen_To_Twenty_Five);
//		Cube_LED(level_1, Column_21, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 72 starting to link witht he first frame
//	{
//		Cube_LED(level_5, Column_3, One_To_Twelve);
//		Cube_LED(level_4, Column_10, One_To_Twelve);
//		Cube_LED(level_3, Column_3, One_To_Twelve);
//		Cube_LED(level_2, Column_11, One_To_Twelve);
//		Cube_LED(level_1, Column_18, Thirteen_To_Twenty_Five);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 73
//	{
//		Cube_LED(level_5, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_4, Column_3, One_To_Twelve);
//		Cube_LED(level_3, Column_10, One_To_Twelve);
//		Cube_LED(level_2, Column_3, One_To_Twelve);
//		Cube_LED(level_1, Column_11, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 74
//	{
//		Cube_LED(level_5, Column_12, One_To_Twelve);
//		Cube_LED(level_4, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_3, Column_3, One_To_Twelve);
//		Cube_LED(level_2, Column_10, One_To_Twelve);
//		Cube_LED(level_1, Column_3, One_To_Twelve);
//	}
//	
//	for(frame=0; frame<time_frame; frame++)//frame 75 Finished joining to the first frame
//	{
//		Cube_LED(level_5, Column_8, One_To_Twelve);
//		Cube_LED(level_4, Column_12, One_To_Twelve);
//		Cube_LED(level_3, Column_13, Thirteen_To_Twenty_Five);
//		Cube_LED(level_2, Column_3, One_To_Twelve);
//		Cube_LED(level_1, Column_10, One_To_Twelve);
//	}
//}

/*---------------------------------------------------------------------*/
void traffic_lights (void)
{
	LED_ON(red);
	if(UserButton()==1)
	{
		LED_ON(orange);
		delay_nms(3000);
		LED_OFF(orange);
		LED_OFF(red);
		LED_ON(green);
		delay_nms(30000);
		LED_OFF(green);
		LED_ON(orange);
		delay_nms(3000);
		LED_OFF(orange);
	}
}
/*---------------------------------------------------------------------*/
void Game_Over(void)//Shows GAME OVER on the front of the cube
{
	Reset_Cube_Array_LEDs();
	
	G_Front_Facing(1500);
	A_Front_Facing(1500);
	M_Front_Facing(1500);
	E_Front_Facing(1500);
	
	delay_nms(500);
	
	O_Front_Facing(1500);
	V_Front_Facing(1500);
	E_Front_Facing(1500);
	R_Front_Facing(1500);
}
/*---------------------------------------------------------------------*/
void Display_Cube_Array_LEDs(int speed)
{
	int x, y, z, i, j; //variables used fro for loops
	int LED;
	int LED_Half;
	int Column;
	int level;
	for(i=0; i<speed; i++)
	{	
		for(z=0; z<5; z++)
		{
			for(j=0; j<3; j++)
			{
				for(y=0; y<5; y++)
				{
					for(x=0; x<5; x++)
					{
						LED = cube_on_off_array[z][y][x];
						Column = Column_Array[y][x];
						level = Level_Array[z];
						
						if((y>1 && x>1)||y>2){
							LED_Half=2;
						}else{
							LED_Half=1;
						}
						
						if(LED==1){
							layer_control(level, Column, LED_Half);
						}
					}
				}
			}
			Cube_Off();
		}
	}
}
/*---------------------------------------------------------------------*/
void A_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 A start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void B_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;

		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;

		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void C_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 G start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][0]=1;
		
		cube_on_off_array[2][i][0]=1;
		
		cube_on_off_array[1][i][0]=1;
		
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void D_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;

		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;

		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void E_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 E start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;

		cube_on_off_array[3][i][0]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		
		cube_on_off_array[1][i][0]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void F_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 E start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;

		cube_on_off_array[3][i][0]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		
		cube_on_off_array[1][i][0]=1;
		
		cube_on_off_array[0][i][0]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void G_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 G start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][0]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void H_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 A start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void I_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 A start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][2]=1;
		
		cube_on_off_array[2][i][2]=1;
		
		cube_on_off_array[1][i][2]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void J_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void K_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 K start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][3]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][3]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void L_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 L start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;

		cube_on_off_array[3][i][0]=1;
		
		cube_on_off_array[2][i][0]=1;
		
		cube_on_off_array[1][i][0]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void M_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 M start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][1]=1;
		cube_on_off_array[3][i][3]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void N_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 M start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][1]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][3]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void O_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void P_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;

		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][0]=1;

		cube_on_off_array[0][i][0]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Q_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 Q start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][3]=1;
		
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void R_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 R start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;

		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void S_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][0]=1;
		
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][4]=1;

		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void T_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 T start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][2]=1;
		
		cube_on_off_array[2][i][2]=1;
		
		cube_on_off_array[1][i][2]=1;
		
		cube_on_off_array[0][i][2]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void U_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 V start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void V_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 V start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][1]=1;
		cube_on_off_array[1][i][3]=1;
		
		cube_on_off_array[0][i][2]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void W_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 W start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][1]=1;
		cube_on_off_array[1][i][3]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void X_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 X start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][1]=1;
		cube_on_off_array[3][i][3]=1;
		
		cube_on_off_array[2][i][2]=1;
		
		cube_on_off_array[1][i][1]=1;
		cube_on_off_array[1][i][3]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Y_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 X start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][1]=1;
		cube_on_off_array[3][i][3]=1;
		
		cube_on_off_array[2][i][2]=1;
		
		cube_on_off_array[1][i][2]=1;
		
		cube_on_off_array[0][i][2]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Z_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 Z start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;
		
		cube_on_off_array[3][i][3]=1;
		
		cube_on_off_array[2][i][2]=1;
		
		cube_on_off_array[1][i][1]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Zero_Front_Facing(int speed)
{
		int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void One_Front_Facing(int speed)
{
		int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][2]=1;
		
		cube_on_off_array[3][i][1]=1;
		cube_on_off_array[3][i][2]=1;
		
		cube_on_off_array[2][i][2]=1;
		
		cube_on_off_array[1][i][2]=1;
		
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Two_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][0]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		cube_on_off_array[0][i][4]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Three_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Four_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][3]=1;
		
		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][3]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][1]=1;
		cube_on_off_array[1][i][2]=1;
		cube_on_off_array[1][i][3]=1;
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Five_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;

		cube_on_off_array[3][i][0]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][4]=1;
		
		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Six_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;

		cube_on_off_array[3][i][0]=1;
		
		cube_on_off_array[2][i][0]=1;
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;

		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Seven_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][0]=1;
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;
		cube_on_off_array[4][i][4]=1;

		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][2]=1;

		cube_on_off_array[0][i][1]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Eight_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;

		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		
		cube_on_off_array[1][i][0]=1;
		cube_on_off_array[1][i][4]=1;

		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Nine_Front_Facing(int speed)
{
	int i;
	
	for(i=0; i<= 4; i++)//Makes a 5x5 O start at the back and move to the front of the cube
	{
		cube_on_off_array[4][i][1]=1;
		cube_on_off_array[4][i][2]=1;
		cube_on_off_array[4][i][3]=1;

		cube_on_off_array[3][i][0]=1;
		cube_on_off_array[3][i][4]=1;
		
		cube_on_off_array[2][i][1]=1;
		cube_on_off_array[2][i][2]=1;
		cube_on_off_array[2][i][3]=1;
		cube_on_off_array[2][i][4]=1;
		
		cube_on_off_array[1][i][4]=1;

		cube_on_off_array[0][i][0]=1;
		cube_on_off_array[0][i][1]=1;
		cube_on_off_array[0][i][2]=1;
		cube_on_off_array[0][i][3]=1;
		
		Display_Cube_Array_LEDs(speed);
		Reset_Cube_Array_LEDs();
	}
}
/*---------------------------------------------------------------------*/
void Score_Front_Facing(int value)
{
	int a, b ,c;
	if(value>999){
		E_Front_Facing(3000);
	}else if(value>99){//3 digits
		a=value/100;//Most significant digit
		b=(value%100)/10;
		c=value%10;
		Display_int(a, 3000);
		Display_int(b, 3000);
		Display_int(c, 3000);
	}else if(value>9){//2 digits
		b=(value%100)/10;
		c=value%10;
		Display_int(b, 3000);
		Display_int(c, 3000);
	}else if(value>=0){//1 digits
		c=value;
		Display_int(c, 3000);
	}
}
/*---------------------------------------------------------------------*/
void Display_int(int value, int speed)
{
	if(value==0){
		Zero_Front_Facing(speed);
	}else if(value==1){
		One_Front_Facing(speed);
	}else if(value==2){
		Two_Front_Facing(speed);
	}else if(value==3){
		Three_Front_Facing(speed);
	}else if(value==4){
		Four_Front_Facing(speed);
	}else if(value==5){
		Five_Front_Facing(speed);
	}else if(value==6){
		Six_Front_Facing(speed);
	}else if(value==7){
		Seven_Front_Facing(speed);
	}else if(value==8){
		Eight_Front_Facing(speed);
	}else if(value==9){
		Nine_Front_Facing(speed);
	}
}
/*---------------------------------------------------------------------*/
void poscube(int a,int i, int delay)// level 1 to 4, col 1 to 20
{
	int a1;
	int i1;
	int i5;
	int i6;
	
	i5 = i + 5;
	i1 = i + 1;
	a1 = a + 1;
	i6 = i + 6;
	
	layer_control(Level_Array[a-1], OneD_Column_Array[i-1], colchecker(i));
	layer_control(Level_Array[a-1], OneD_Column_Array[i1-1], colchecker(i1));
	layer_control(Level_Array[a-1], OneD_Column_Array[i5-1], colchecker(i5));
	layer_control(Level_Array[a-1], OneD_Column_Array[i6-1], colchecker(i6));
	layer_control(Level_Array[a1-1], OneD_Column_Array[i-1], colchecker(i));
	layer_control(Level_Array[a1-1], OneD_Column_Array[i1-1], colchecker(i1));
	layer_control(Level_Array[a1-1], OneD_Column_Array[i5-1], colchecker(i5));
	layer_control(Level_Array[a1-1], OneD_Column_Array[i6-1], colchecker(i6));

	delay_nms(delay);	
	Cube_Off();	
}
/*---------------------------------------------------------------------*/
int colchecker (int input)
{
	if (input <= 12){
	  return One_To_Twelve;
	}else{
		return Thirteen_To_Twenty_Five;
	}
}
/*---------------------------------------------------------------------*/
//void random_travel_cube(void)
//{
//	int b;
//	int delay = 200;
//	b = (rand()%7 + 1);
//	
//	if (cube_travel_posy==1){
//		if (b==1){
//			poscube(1,2,delay);
//			poscube(1,3,delay);
//			poscube(1,4,delay);
//			cube_travel_posy=2;
//			return;
//		}else if (b==2){
//			poscube(1,6,delay);
//			poscube(1,11,delay);
//			poscube(1,16,delay);
//			cube_travel_posy=3;
//			return;
//		}else if (b==3){
//			poscube(2,1,delay);
//			poscube(3,1,delay);
//			poscube(4,1,delay);
//			cube_travel_posy=5;
//			return;
//		}else if (b==4){
//			poscube(1,7,delay);
//			poscube(1,13,delay);
//			poscube(1,19,delay);
//			cube_travel_posy=4;
//			return;
//		}else if (b==5){
//			poscube(2,2,delay);
//			poscube(3,3,delay);
//			poscube(4,4,delay);
//			cube_travel_posy=6;
//			return;
//		}else if (b==6){
//			poscube(2,6,delay);
//			poscube(3,11,delay);
//			poscube(4,16,delay);
//			cube_travel_posy=7;
//			return;
//		}else{
//			poscube(2,7,delay);
//			poscube(3,13,delay);
//			poscube(4,19,delay);
//			cube_travel_posy=8;
//			return;
//		}	
//	}else if (cube_travel_posy==2){
//	if (b==1){
//			poscube(1,9,delay);
//			poscube(1,14,delay);
//			poscube(1,19,delay);
//			cube_travel_posy=4;
//			return;
//		}else if (b==2){
//			poscube(1,3,delay);
//			poscube(1,2,delay);
//			poscube(1,1,delay);
//			cube_travel_posy=1;
//			return;
//		}else if (b==3){
//			poscube(2,4,delay);
//			poscube(3,4,delay);
//			poscube(4,4,delay);
//			cube_travel_posy=6;
//			return;
//		}else if (b==4){
//			poscube(1,8,delay);
//			poscube(1,12,delay);
//			poscube(1,16,delay);
//			cube_travel_posy=3;
//			return;
//		}else if (b==5){
//			poscube(2,3,delay);
//			poscube(3,2,delay);
//			poscube(4,1,delay);
//			cube_travel_posy=5;
//			return;
//		}else if (b==6){
//			poscube(2,9,delay);
//			poscube(3,14,delay);
//			poscube(4,19,delay);
//			cube_travel_posy=8;
//			return;
//		}else{
//			poscube(2,8,delay);
//			poscube(3,12,delay);
//			poscube(4,16,delay);
//			cube_travel_posy=7;
//			return;
//		}
//	
//	}else if (cube_travel_posy==3){
//	if (b==1){
//			poscube(1,11,delay);
//			poscube(1,6,delay);
//			poscube(1,1,delay);
//			cube_travel_posy=1;
//			return;
//		}else if (b==2){
//			poscube(1,17,delay);
//			poscube(1,18,delay);
//			poscube(1,19,delay);
//			cube_travel_posy=4;
//			return;
//		}else if (b==3){
//			poscube(2,16,delay);
//			poscube(3,16,delay);
//			poscube(4,16,delay);
//			cube_travel_posy=7;
//			return;
//		}else if (b==4){
//			poscube(1,12,delay);
//			poscube(1,8,delay);
//			poscube(1,4,delay);
//			cube_travel_posy=2;
//			return;
//		}else if (b==5){
//			poscube(2,17,delay);
//			poscube(3,18,delay);
//			poscube(4,19,delay);
//			cube_travel_posy=8;
//			return;
//		}else if (b==6){
//			poscube(2,11,delay);
//			poscube(3,6,delay);
//			poscube(4,1,delay);
//			cube_travel_posy=5;
//			return;
//		}else{
//			poscube(2,12,delay);
//			poscube(3,8,delay);
//			poscube(4,4,delay);
//			cube_travel_posy=6;
//			return;
//		}
//		
//		}else if (cube_travel_posy==4){
//	if (b==1){
//			poscube(1,18,delay);
//			poscube(1,17,delay);
//			poscube(1,16,delay);
//			cube_travel_posy=3;
//			return;
//		}else if (b==2){
//			poscube(1,14,delay);
//			poscube(1,9,delay);
//			poscube(1,4,delay);
//			cube_travel_posy=2;
//			return;
//		}else if (b==3){
//			poscube(2,19,delay);
//			poscube(3,19,delay);
//			poscube(4,19,delay);
//			cube_travel_posy=8;
//			return;
//		}else if (b==4){
//			poscube(1,13,delay);
//			poscube(1,7,delay);
//			poscube(1,1,delay);
//			cube_travel_posy=1;
//			return;
//		}else if (b==5){
//			poscube(2,14,delay);
//			poscube(3,9,delay);
//			poscube(4,4,delay);
//			cube_travel_posy=6;
//			return;
//		}else if (b==6){
//			poscube(2,18,delay);
//			poscube(3,17,delay);
//			poscube(4,16,delay);
//			cube_travel_posy=7;
//			return;
//		}else{
//			poscube(2,13,delay);
//			poscube(3,7,delay);
//			poscube(4,1,delay);
//			cube_travel_posy=5;
//			return;
//		}
//		
//		}else if (cube_travel_posy==5){
//	if (b==1){
//			poscube(4,2,delay);
//			poscube(4,3,delay);
//			poscube(4,4,delay);
//			cube_travel_posy=6;
//			return;
//		}else if (b==2){
//			poscube(4,6,delay);
//			poscube(4,11,delay);
//			poscube(4,16,delay);
//			cube_travel_posy=7;
//			return;
//		}else if (b==3){
//			poscube(3,1,delay);
//			poscube(2,1,delay);
//			poscube(1,1,delay);
//			cube_travel_posy=1;
//			return;
//		}else if (b==4){
//			poscube(4,7,delay);
//			poscube(4,13,delay);
//			poscube(4,19,delay);
//			cube_travel_posy=8;
//			return;
//		}else if (b==5){
//			poscube(3,2,delay);
//			poscube(2,3,delay);
//			poscube(1,4,delay);
//			cube_travel_posy=2;
//			return;
//		}else if (b==6){
//			poscube(3,6,delay);
//			poscube(2,11,delay);
//			poscube(1,16,delay);
//			cube_travel_posy=3;
//			return;
//		}else{
//			poscube(3,7,delay);
//			poscube(2,13,delay);
//			poscube(1,19,delay);
//			cube_travel_posy=4;
//			return;
//		}
//		
//		}else if (cube_travel_posy==6){
//	if (b==1){
//			poscube(4,3,delay);
//			poscube(4,2,delay);
//			poscube(4,1,delay);
//			cube_travel_posy=5;
//			return;
//		}else if (b==2){
//			poscube(4,9,delay);
//			poscube(4,14,delay);
//			poscube(4,19,delay);
//			cube_travel_posy=8;
//			return;
//		}else if (b==3){
//			poscube(3,4,delay);
//			poscube(2,4,delay);
//			poscube(1,4,delay);
//			cube_travel_posy=2;
//			return;
//		}else if (b==4){
//			poscube(4,8,delay);
//			poscube(4,12,delay);
//			poscube(4,16,delay);
//			cube_travel_posy=7;
//			return;
//		}else if (b==5){
//			poscube(3,3,delay);
//			poscube(2,2,delay);
//			poscube(1,1,delay);
//			cube_travel_posy=1;
//			return;
//		}else if (b==6){
//			poscube(3,9,delay);
//			poscube(2,14,delay);
//			poscube(1,19,delay);
//			cube_travel_posy=4;
//			return;
//		}else{
//			poscube(3,8,delay);
//			poscube(2,12,delay);
//			poscube(1,16,delay);
//			cube_travel_posy=3;
//			return;
//		}
//		
//		}else if (cube_travel_posy==7){
//	if (b==1){
//			poscube(4,17,delay);
//			poscube(4,18,delay);
//			poscube(4,19,delay);
//			cube_travel_posy=8;
//			return;
//		}else if (b==2){
//			poscube(4,11,delay);
//			poscube(4,6,delay);
//			poscube(4,1,delay);
//			cube_travel_posy=5;
//			return;
//		}else if (b==3){
//			poscube(3,16,delay);
//			poscube(2,16,delay);
//			poscube(1,16,delay);
//			cube_travel_posy=3;
//			return;
//		}else if (b==4){
//			poscube(4,12,delay);
//			poscube(4,8,delay);
//			poscube(4,4,delay);
//			cube_travel_posy=6;
//			return;
//		}else if (b==5){
//			poscube(3,17,delay);
//			poscube(2,18,delay);
//			poscube(1,19,delay);
//			cube_travel_posy=4;
//			return;
//		}else if (b==6){
//			poscube(3,11,delay);
//			poscube(2,6,delay);
//			poscube(1,1,delay);
//			cube_travel_posy=1;
//			return;
//		}else{
//			poscube(3,12,delay);
//			poscube(2,8,delay);
//			poscube(1,4,delay);
//			cube_travel_posy=2;
//			return;
//		}
//		
//		}else if (cube_travel_posy==8){
//	if (b==1){
//			poscube(4,18,delay);
//			poscube(4,17,delay);
//			poscube(4,16,delay);
//			cube_travel_posy=7;
//			return;
//		}else if (b==2){
//			poscube(4,14,delay);
//			poscube(4,9,delay);
//			poscube(4,4,delay);
//			cube_travel_posy=6;
//			return;
//		}else if (b==3){
//			poscube(3,19,delay);
//			poscube(2,19,delay);
//			poscube(1,19,delay);
//			cube_travel_posy=4;
//			return;
//		}else if (b==4){
//			poscube(4,13,delay);
//			poscube(4,7,delay);
//			poscube(4,1,delay);
//			cube_travel_posy=5;
//			return;
//		}else if (b==5){
//			poscube(3,18,delay);
//			poscube(2,17,delay);
//			poscube(1,16,delay);
//			cube_travel_posy=3;
//			return;
//		}else if (b==6){
//			poscube(3,14,delay);
//			poscube(2,9,delay);
//			poscube(1,4,delay);
//			cube_travel_posy=2;
//			return;
//		}else{
//			poscube(3,13,delay);
//			poscube(2,7,delay);
//			poscube(1,1,delay);
//			cube_travel_posy=1;
//			return;
//		}
//	}
//}
/*---------------------------------------------------------------------*/
