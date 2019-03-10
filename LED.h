#ifndef __LED_H
#define __LED_H
#define green 12
#define orange 13
#define red 14
#define blue 15

//Defines for the ground levels
#define level_1 1
#define level_2 2
#define level_3 3
#define level_4 8
#define level_5 15

//Defines for the columns
#define Column_1 0
#define Column_2 1
#define Column_3 6
#define Column_4 4
#define Column_5 5
#define Column_6 7
#define Column_7 8
#define Column_8 11
#define Column_9 12
#define Column_10 13
#define Column_11 14
#define Column_12 15
#define Column_13 2
#define Column_14 4
#define Column_15 5
#define Column_16 6
#define Column_17 7
#define Column_18 8
#define Column_19 9
#define Column_20 10
#define Column_21 11
#define Column_22 12
#define Column_23 13
#define Column_24 14
#define Column_25 15

//Defines for the what LEDs can be controlled
#define Off 0
#define One_To_Twelve 1
#define Thirteen_To_Twenty_Five 2
#define PI 3.14159265358979323846

void LEDinit(void);
void LED_ON(int x);
void LED_OFF(int x);
void ALL_LED_ON(void);
void ALL_ONBOARD_LED_OFF(void);
void PWM (int x, int s, int LED); 
void External_PWM (int x, int s, int LED);
void External_LED_ON(int LED);
void External_LED_OFF(int LED);
void ALL_External_LED_OFF(void);
void LED_Voltage_Display(int mV);
void ground_level (int level);
void LED_column (int column, int Half);
void Cube_LED (int level, int column, int Half);
void Cycle_All_LEDs (int delay);
void Cube_Off(void);
void layer_control(int level, int column, int Half);
void Cube_On(void);
void Edges(int time_frame);
void Rain(int time_frame);
void One_Top(void);
void Dice(int number, int time_frame);
int random_1_to_6(void);
int getRandomNumber(void);
void Sphere(int time_frame);
void sinewave(int time_frame);
void Heartbeat (void);
void Analogue_LED(void);
void Random_LED(int delay);
void Spiral (int speed);
void Cube_sine(int speed);
void Cube_Double_sine(int speed);
void Cube_Array_LEDs(int x, int y, int z, int On_Off);
void Reset_Cube_Array_LEDs(void);
void Display_Cube_Array_LEDs_Snake(int speed);
void Snake_Game(void);
void Face_On(int face);
void Non_Repeating_Random_LEDs(int On_Off);
void To_Array_125(int input, int On_Off);
void Display_Cube_Array_LEDs(int speed);
void Game_Over(void);
void Zero_Front_Facing(int speed);
void One_Front_Facing(int speed);
void Two_Front_Facing(int speed);
void Three_Front_Facing(int speed);
void Four_Front_Facing(int speed);
void Five_Front_Facing(int speed);
void Six_Front_Facing(int speed);
void Seven_Front_Facing(int speed);
void Eight_Front_Facing(int speed);
void Nine_Front_Facing(int speed);
void Display_int(int value, int speed);
void Score_Front_Facing(int value);
void A_Front_Facing(int speed);
void B_Front_Facing(int speed);
void C_Front_Facing(int speed);
void D_Front_Facing(int speed);
void E_Front_Facing(int speed);
void F_Front_Facing(int speed);
void G_Front_Facing(int speed);
void H_Front_Facing(int speed);
void I_Front_Facing(int speed);
void J_Front_Facing(int speed);
void K_Front_Facing(int speed);
void L_Front_Facing(int speed);
void M_Front_Facing(int speed);
void N_Front_Facing(int speed);
void O_Front_Facing(int speed);
void P_Front_Facing(int speed);
void Q_Front_Facing(int speed);
void R_Front_Facing(int speed);
void S_Front_Facing(int speed);
void T_Front_Facing(int speed);
void U_Front_Facing(int speed);
void V_Front_Facing(int speed);
void W_Front_Facing(int speed);
void X_Front_Facing(int speed);
void Y_Front_Facing(int speed);
void Z_Front_Facing(int speed);
void traffic_lights (void);
void Cube_3x3x3_Pulsing(int pulse_speed, int range, int offset);
void random_travel_cube(void);
void poscube(int a,int i, int delay);
int levs (int input);
int col (int input);
int colchecker (int input);
void Ultrasonic_Move_LED(int cmx, int cmy, int cmz);

#endif
