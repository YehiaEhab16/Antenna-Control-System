#include <Arduino.h>
#include "Modules.h" 

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

void Forward(void)
{
  Motor_ForwardDirection();
  LED_Forward();
  Serial.println("Forward");
}
void Backward(void)
{
  Motor_BackwardDirection();
  LED_Backward();
  Serial.println("Backward");
}
void Stop(void)
{
  Motor_Stop();
  LED_Stop();
  Serial.println("Stop");
}

void Init(void)
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

double Encoder_Read(void)
{
  double Angle=0;     //Angle to be returned
  int Serial_Read=0;  //Variable to read data coming from serial 
  while (Serial.available())
  {
    Serial_Read=Serial.read();//Reading from serial
    if(Serial_Read==NEGATIVE_SIGN || Serial_Read==POSITIVE_SIGN) //Checking for stop bits '+' or '-'
      break;
    Angle=Serial_Read;  //Getting angle value from serial
  }
  if(Serial_Read==NEGATIVE_SIGN && Angle>0)
    Angle*=-1;          //Setting the angle to be negative according to the sent sign 
  return Angle;
}

int Calculate_Speed(int Voltage)
{
  //Divide voltage by 2 due to OP_Amp amplification
  int Speed=(((Voltage/2.0)*255)/5.0);    //Map the voltage value to the range of analog write function (0->255)
  return Speed;
}

void Serial_Print(int cAngle,int dAngle, int Out)
{
  Serial.print("Current Angle=");
  Serial.println(cAngle);
  Serial.print("Diff Angle=");
  Serial.println(dAngle);
  Serial.print("Output=");
  Serial.println(abs(Out));
}

