#include <SoftwareSerial.h>         //Including SoftwareSerial library to connect with bluetooth module
#include "Modules.h"                //Including the defined library 'Modules'
#include "App_Functions.h"          //Including the defined library 'App_Functions'

//Bluetooth module for Mobile Application
SoftwareSerial mySerial(RX, TX);

//Declaration of global variables
int CurrentAngle=0,DesiredAngle,DiffAngle,Time,Speed;
String inputString = "";        //Variable that holds the recieved string
bool stringComplete = false;    //Flag to indicate recieving of string from application or LabView

//ISRs for external interrupt
void Min_Limit_Reached();
void Max_Limit_Reached();

void setup() {
  //Initalizing needed pins as output
  Initialize();

  //Attaching interrupts at pins 0&1
  attachInterrupt(INTERRUPT_ID1,Min_Limit_Reached,RISING);
  attachInterrupt(INTERRUPT_ID2,Max_Limit_Reached,RISING);

  //Initalizing serial & software serial connection
  mySerial.begin(9600);   
  Serial.begin(9600);
  Serial.println("Initializing CODE...");
}

void loop() {
  //Checking data from applcation
   if(mySerial.available())
  {
    inputString=mySerial.readString();
    Serial.println("Mobile Application Mode");
    stringComplete=true;
  }
  if (stringComplete) //Checking for flag
  {
    DesiredAngle = inputString.toInt();     //Converting to integer
    inputString = "";                       //Clearing string
    stringComplete = false;                 //Clearing Flag
    DiffAngle = DesiredAngle - CurrentAngle;//Calculating difference between desired and current angle
    Serial.print("Angle=");
    Serial.println(abs(DiffAngle));

    //Determining direction according to the difference
    if(DiffAngle>0)
    {
      Forward();
    }
    else if(DiffAngle<0)
    {
      Backward();
    }
      
    //Determining speed according to the difference
    //Case1: Low speed operation
    if((abs(DiffAngle)<THRESHOLD_ANGLE)&&(abs(DiffAngle)>0))
    {
      Low_Speed_Op();
    }
    //Case2: High speed operation
    else if(abs(DiffAngle)>THRESHOLD_ANGLE)
    {
      //The motor will first start at low speed for 5 degrees ,then it will continue with high speed until it reaches the last 5 degrees which will also be in low speed
      //Low speed interval
      Serial.println("HIGH SPEED");
      if(DiffAngle!=0)
      {
        Accelerating();
      }

      //High speed interval
      if(DiffAngle!=0)
      {
        High_Speed_Op();
      }

      //Low speed interval
      if(DiffAngle!=0)
      {
        Decelerating();
      }
      Stop();
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
      Serial.println("LabView GUI Mode");
      stringComplete = true;             //Setting flag to indicate recieving of string
    }
    if(!stringComplete)
      inputString += inChar;            //Concatenating string until reaching full message
  }
}

//ISR when reaching minimum limit
void Min_Limit_Reached()
{
  Min_Interrupt();
}
//ISR when reaching minimum limit
void Max_Limit_Reached()
{
  Max_Interrupt();
}
