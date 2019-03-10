#include <stm32f4xx.h>
#include "delay.h"
#include "LED.h"
#include <stdio.h>
#include "ADCDAC.h"
#include <math.h>
#include "Switch.h"
#include "menu.h"
#include "core_cm4.h"
#include <Stdlib.h>

int delay;
int delay2;
int i=0;
int cycle;	

//int l, count=1;
int main(void){
	Init_Init(); //initialises everything
	Cube_Off();
	//displays double sine and seeds the random
//while(analogue_direction_1()==0 && analogue_direction_2()==0)
//	{
//		srand(i);
//		i++;
//		Cube_Double_sine(50);
//	}
//	
//	while(analogue_direction_1()!=0 || analogue_direction_2()!=0){}
//	delay_nms(10);
	
	while(1)
	{
		GPIOD->ODR ^=(1UL << green);
		Ultrasonic_distance_xyz();
		
		//Score_Front_Facing(Return_Ultrasonic (1));
		Ultrasonic_Move_LED(Return_Ultrasonic (0), Return_Ultrasonic (1), Return_Ultrasonic (2));
		//Score_Front_Facing(Ultrasonic_distance());
//		delay_nms(50);
		//Ultrasonic_Move_LED(Ultrasonic_distance());
		//delay_nms(15);
		//traffic_lights ();
		
//		for(cycle=0; cycle<200; cycle++)
//		{
//			Rain(800);
//		}
//		
//		for(cycle=0; cycle<1000; cycle++)
//		{
//			Cube_3x3x3_Pulsing(100, 130, 230); //About 50 for speed and 100 for range
//		}
//		
//		for(cycle=0; cycle<2500; cycle++)
//		{
//			Cube_sine(40);
//		}
//		
//		for(cycle=0; cycle<20; cycle++)
//		{
//			random_travel_cube();
//		}
//		
//		for(cycle=0; cycle<3; cycle++)
//		{
//			Non_Repeating_Random_LEDs(1);
//			Non_Repeating_Random_LEDs(0);
//		}
//		
//		for(cycle=0; cycle<2500; cycle++)
//		{
//			Cube_Double_sine(50);
//		}
//		
//		for(cycle=0; cycle<200; cycle++)
//		{
//			Random_LED(100);
//		}
//		
//		for(cycle=0; cycle<500000; cycle++)
//		{
//			Cube_On();
//		}
//		
//		Cube_Off();

//for(cycle=0; cycle<200; cycle++)
//{
//	for(delay=0; delay<30000; delay++)
//	{
//	delay2=delay/1000+5;
//		sinewave(delay2);
//	}
//	for(delay=30000; delay>=0; delay--)
//	{
//		delay2=delay/1000+5;
//		sinewave(delay2);
//	}
//}
//Reset_Cube_Array_LEDs();
//Snake_Game();
//int q;
//for(q=0; q<10; q++)
//{
//	Display_int(q, 4000);
//}
//Score_Front_Facing(23);
//Game_Over();
//M_Front_Facing(20000);
//Face_On(0);
//int i;
//for(i=0; i<2000000; i++)
//{
//	if(i==1){
//	Analogue_LED();
//	}
//}
//Edges(100);
//Spiral(3000);
//Cube_Off();
//Cycle_All_LEDs (100);
//Heartbeat();
//One_Top();
//Dice(random_1_to_6(), 900000);
//Sphere(200);
//A_Front_Facing(2000);
//B_Front_Facing(2000);
//C_Front_Facing(2000);
//D_Front_Facing(2000);
//E_Front_Facing(2000);
//F_Front_Facing(2000);
//G_Front_Facing(2000);
//H_Front_Facing(2000);
//I_Front_Facing(2000);
//J_Front_Facing(2000);
//K_Front_Facing(2000);
//L_Front_Facing(2000);
//M_Front_Facing(2000);
//N_Front_Facing(2000);
//O_Front_Facing(2000);
//P_Front_Facing(2000);
//Q_Front_Facing(2000);
//R_Front_Facing(2000);
//S_Front_Facing(2000);
//T_Front_Facing(2000);
//U_Front_Facing(2000);
//V_Front_Facing(2000);
//W_Front_Facing(2000);
//X_Front_Facing(2000);
//Y_Front_Facing(2000);
//Z_Front_Facing(2000);
	} //End of while
}		//End of main
