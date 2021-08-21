#include <Arduino.h>

void Motor_ForwardDirection(int ForwardPin,int BackwardPin)
{
  digitalWrite(ForwardPin,HIGH);
  digitalWrite(BackwardPin,LOW);
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
int Calculate_Time(int Angle,int Speed,int Gear)
{
  int Time=(Angle/(Speed*6.0/(Gear)))*1000;
  return Time;
}
void Calculate_Speed(int Voltage)
{
  int Speed=(((Voltage/2.0)*255)/5.0);
  return Speed;
}

