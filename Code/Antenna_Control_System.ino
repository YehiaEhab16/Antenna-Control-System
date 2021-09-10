#include <SoftwareSerial.h>         //Including SoftwareSerial library to connect with bluetooth module
#include "Modules.h"                //Including the defined library 'Modules'

//Bluetooth module for Mobile Application
SoftwareSerial mySerial(RX, TX);

//Declaration of global variables
int CurrentAngle=0,DesiredAngle,DiffAngle,Speed,Time,TotalTime=0,FinalAngle=0;
String inputString = "";        //Variable that holds the recieved string
bool stringComplete = false,dir_flag=FORWARD,speed_flag=LOW_SPEED_OP,src_flag=APP;    //Flag to indicate recieving of string from application or LabView

//ISRs for external interrupt
void Min_Limit_Reached();
void Max_Limit_Reached();

void setup() 
{
  //Initaliziation
   Init();

   //Initalizing software serial connection
   mySerial.begin(9600);  

   //Attaching interrupts at pins 0&1
   attachInterrupt(INTERRUPT_ID1,Min_Limit_Reached,RISING);
   attachInterrupt(INTERRUPT_ID2,Max_Limit_Reached,RISING);
}

void loop() {
  //Checking data from applcation
   if(mySerial.available())
  {
    inputString=mySerial.readString();
    src_flag=APP;         //Flag to indicate that the sender is mobile application 
    stringComplete=true;  //Flag to indicate the completion of the string
  }
  if (stringComplete) //Checking for flag
  {
    DesiredAngle = inputString.toInt();     //Converting to integer
    inputString = "";                       //Clearing string
    stringComplete = false;                 //Clearing Flag
    DiffAngle = DesiredAngle - CurrentAngle;//Calculating difference between desired and current angle
    FinalAngle=DiffAngle;                    //Angle to be sended to labview

    //Determining direction according to the difference
    if(DiffAngle>0)
    {
      Forward(&dir_flag);
    }
    else if(DiffAngle<0)
    {
      Backward(&dir_flag);
    }
      
    //Determining speed according to the difference
    //Case1: Low speed operation
    if((abs(DiffAngle)<THRESHOLD_ANGLE)&&(abs(DiffAngle)>0))
    {
      Low_Speed_Op(&TotalTime,&speed_flag,DiffAngle);
    }
    //Case2: High speed operation
    else if(abs(DiffAngle)>THRESHOLD_ANGLE)
    {
      //The motor will first start at low speed for 5 degrees ,then it will continue with high speed until it reaches the last 5 degrees which will also be in low speed
      //Low speed interval
      speed_flag=HIGH_SPEED_OP;
      if(DiffAngle!=0)
      {
        Slow_Down(&TotalTime);
      }

      //High speed interval
      if(DiffAngle!=0)
      {
        High_Speed_Op(&TotalTime,DiffAngle);
      }

      //Low speed interval
      if(DiffAngle!=0)
      {
        Slow_Down(&TotalTime);
        Stop();
      }
    }
    if(DiffAngle!=0)
    {
      Serial_Print(&TotalTime,FinalAngle,src_flag,dir_flag,speed_flag);   //Sending all data to labview to be printed
    }
    CurrentAngle=DesiredAngle;    //Updating current angle after reaching desired position
  }
}

//For read from write buffer
void serialEvent() 
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();   //Reading character from serial
    if (inChar == '#')                   //Checking for stop bit '#'
    {
      src_flag=GUI;                      //Flag to indicate that the sender is labview
      stringComplete = true;             //Setting flag to indicate recieving of string
    }
    if(!stringComplete)
      inputString += inChar;            //Concatenating string until reaching full message
  }
}

//ISR when reaching minimum limit
void Min_Limit_Reached()
{
  Serial.println("Min Interrupt");
  Motor_Stop();
  LED_Stop();
  Serial.println("STOP MOTOR");
  DiffAngle=0;
  Speed=0;
  DesiredAngle=MIN_ANGLE;
}
//ISR when reaching minimum limit
void Max_Limit_Reached()
{
  Serial.println("Max Interrupt");
  Motor_Stop();
  LED_Stop();
  Serial.println("STOP MOTOR");
  DiffAngle=0;
  Speed=0;
  DesiredAngle=MAX_ANGLE;
}
