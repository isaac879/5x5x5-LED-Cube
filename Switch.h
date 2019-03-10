#ifndef __Switch_H
#define __Switch_H

#define forward 1
#define backward 2
#define left 3
#define right 4
#define up 1
#define down 2

int UserButton(void);
int UserSwitch1(void);	
int UserSwitch2(void);
int UserSwitch3(void);
int UserSwitch4(void);
int DC_Variable_Voltage (void);
int Reed_SwitchB(void);
int Reed_SwitchA(void);
int Distance_Traveled(void);
int analogue_direction_1(void);
int analogue_direction_2(void);
void Trigger_On(void);
void Trigger_Off(void);
int Ultrasonic_distance(void);
int ultrasonic_sensor_echo_x(void);
int ultrasonic_sensor_echo_y(void);
int ultrasonic_sensor_echo_z(void);
void Ultrasonic_distance_xyz(void);
int Return_Ultrasonic (int xyz);

#endif
