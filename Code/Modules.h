#ifndef MODULES_H_
#define MODULES_H_

void Motor_ForwardDirection(int ForwardPin,int BackwardPin);
void Motor_BackwardDirection(int ForwardPin,int BackwardPin);
void Motor_SetSpeed(int SpeedPin,int Speed);
void Motor_Stop(int ForwardPin,int BackwardPin,int SpeedPin);

void LED_Foraward(int ForwardInd,int BackwardInd,int StopInd);
void LED_Backward(int ForwardInd,int BackwardInd,int StopInd);
void LED_Stop(int ForwardInd,int BackwardInd,int StopInd);

int Calculate_Time(int Angle,int Speed,int Gear);
int Calculate_Speed(int Voltage);

#endif
