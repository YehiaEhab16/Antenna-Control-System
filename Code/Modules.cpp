#include <Arduino.h>

void Motor_ForwardDirection(int ForwardPin,int BackwardPin)
{
  digitalWrite(BackwardPin,LOW);
  digitalWrite(ForwardPin,HIGH);
}
void Motor_BackwardDirection(int ForwardPin,int BackwardPin)
{
  digitalWrite(ForwardPin,LOW);
  digitalWrite(BackwardPin,HIGH);
}
void Motor_SetSpeed(int SpeedPin,int Speed)
{
  analogWrite(SpeedPin,Speed);
}
void Motor_Stop(int ForwardPin,int BackwardPin,int SpeedPin)
{
  digitalWrite(ForwardPin,LOW);
  digitalWrite(BackwardPin,LOW);
  digitalWrite(SpeedPin,LOW);
}

void LED_Forward(int ForwardInd,int BackwardInd,int StopInd)
{
  digitalWrite(BackwardInd,LOW);
  digitalWrite(StopInd,LOW);
  digitalWrite(ForwardInd,HIGH);
}
void LED_Backward(int ForwardInd,int BackwardInd,int StopInd)
{
  digitalWrite(ForwardInd,LOW);
  digitalWrite(StopInd,LOW);
  digitalWrite(BackwardInd,HIGH);
}
void LED_Stop(int ForwardInd,int BackwardInd,int StopInd)
{
  digitalWrite(ForwardInd,LOW);
  digitalWrite(BackwardInd,LOW);
  digitalWrite(StopInd,HIGH);
}

int Calculate_Time(int Angle,int Speed,int Gear)
{
  //Dividng angle by angle per speed
  int Time=(Angle/(Speed*6.0/(Gear)))*1000;   //Angle per speed = RPM *360/60 /Gear
  //Multiply by 1000 to convert to milliseconds
  return Time;
}
int Calculate_Speed(int Voltage)
{
  //Divide voltage by 2 due to OP_Amp amplification
  int Speed=(((Voltage/2.0)*255)/5.0);    //Map the voltage value to the range of analog write function (0->255)
  return Speed;
}

