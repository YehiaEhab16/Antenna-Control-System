#include <Arduino.h>
#include "Modules.h"

extern int Speed,Time;

void Motor_ForwardDirection(void)
{
  digitalWrite(DIR_BACK,LOW);
  digitalWrite(DIR_FOR,HIGH);
}
void Motor_BackwardDirection(void)
{
  digitalWrite(DIR_FOR,LOW);
  digitalWrite(DIR_BACK,HIGH);
}
void Motor_SetSpeed(int Speed)
{
  analogWrite(MOTOR_SPEED,Speed);
}
void Motor_Stop(void)
{
  digitalWrite(DIR_FOR,LOW);
  digitalWrite(DIR_BACK,LOW);
  digitalWrite(MOTOR_SPEED,LOW);
}

void LED_Forward(void)
{
  digitalWrite(BACK_LED,LOW);
  digitalWrite(STOP_LED,LOW);
  digitalWrite(FOR_LED,HIGH);
}
void LED_Backward(void)
{
  digitalWrite(FOR_LED,LOW);
  digitalWrite(STOP_LED,LOW);
  digitalWrite(BACK_LED,HIGH);
}
void LED_Stop(void)
{
  digitalWrite(FOR_LED,LOW);
  digitalWrite(BACK_LED,LOW);
  digitalWrite(STOP_LED,HIGH);
}

int Calculate_Time(int Angle,int Speed)
{
  //Dividng angle by angle per speed
  int Time=(Angle/(Speed*6.0/(GEARBOX_RATIO)))*1000;   //Angle per speed = RPM *360/60 /Gear
  //Multiply by 1000 to convert to milliseconds
  return Time;
}
int Calculate_Speed(int Voltage)
{
  //Divide voltage by 2 due to OP_Amp amplification
  int Speed=(((Voltage/2.0)*255)/5.0);    //Map the voltage value to the range of analog write function (0->255)
  return Speed;
}

void Init()
{
  //Initalizing needed pins as output
  pinMode(DIR_FOR,OUTPUT);
  pinMode(DIR_BACK,OUTPUT);
  pinMode(MOTOR_SPEED,OUTPUT);
  pinMode(FOR_LED,OUTPUT);
  pinMode(BACK_LED,OUTPUT);
  pinMode(STOP_LED,OUTPUT);

  //Initalizing serial connection
  Serial.begin(9600);
  Serial.println("Initializing CODE...");
}

void Forward(bool* flag)
{
  Motor_ForwardDirection();
  LED_Forward();
  *flag=FORWARD;
}
void Backward(bool* flag)
{
  Motor_BackwardDirection();
  LED_Backward();
  *flag=BACKWARD;
}
void Stop(void)
{
  Motor_Stop();
  LED_Stop();
}

void Low_Speed_Op(int* Total,bool* flag,int Angle)
{
  Time = Calculate_Time(abs(Angle),MOTOR_LOW_SPEED);
  *Total+=Time;
  Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);
  Motor_SetSpeed(Speed);
  delay(Time);
  Motor_Stop();
  LED_Stop();
  *flag=LOW_SPEED_OP ;
}
void Slow_Down(int* Total)
{
  Time = Calculate_Time(DEC_ANGLE,MOTOR_LOW_SPEED);
  *Total+=Time;
  Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);
  Motor_SetSpeed(Speed);
  delay(Time);
}
void High_Speed_Op(int* Total,int Angle)
{
  Angle = abs(Angle)-2*DEC_ANGLE;
  Time = Calculate_Time(Angle,MOTOR_HIGH_SPEED);
  *Total+=Time;
  Speed = Calculate_Speed(HIGH_SPEED_VOLTAGE);
  Motor_SetSpeed(Speed);
  delay(Time);
}

void Serial_Print(int* Time,int Angle,bool src_flag,bool dir_flag,bool speed_flag)
{
  Serial.println((src_flag==APP)? "Mobile Application Mode":"LabView GUI Mode");
  delay(LABVIEW_DELAY);
  Serial.print("Angle=");
  Serial.println(Angle);
  delay(LABVIEW_DELAY);
  Serial.println((dir_flag==FORWARD)? "Forward":"Backward");
  delay(LABVIEW_DELAY);
  Serial.println((speed_flag==LOW_SPEED_OP)? "Low Speed":"High Speed");
  delay(LABVIEW_DELAY);
  Serial.print("Time=");
  Serial.println(*Time);
  delay(LABVIEW_DELAY);
  *Time=0;
}

