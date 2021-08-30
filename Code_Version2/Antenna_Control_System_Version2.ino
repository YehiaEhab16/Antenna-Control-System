#include "Modules.h"                //Including the defined library 'Modules'
#include "App_Functions.h"          //Including the defined library 'App_Functions'

//Declaration of global variables
int CurrentAngle=0,DesiredAngle,DiffAngle,Time,Speed;
String inputString = "";
bool stringComplete = false;

//ISR for external interrupt
void Min_Limit_Reached();
void Max_Limit_Reached();

void setup() {
  //Initalizing needed pins as output
  Initialize();
  
  attachInterrupt(INTERRUPT_ID1,Min_Limit_Reached,RISING);
  attachInterrupt(INTERRUPT_ID2,Max_Limit_Reached,RISING);

  Serial.begin(9600);               //Initalizing serial connection
  Serial.println("Initializing CODE...");
}

void loop() {
  if (stringComplete)
  {
    DesiredAngle = inputString.toInt();
    inputString = "";
    stringComplete = false;
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
    CurrentAngle=DesiredAngle;    //Updating current angle after the operation
  }
}

//For read from write buffer
void serialEvent() 
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '#') 
    {
      stringComplete = true;
    }
    if(!stringComplete)
      inputString += inChar;
  }
}

void Min_Limit_Reached()
{
  Min_Interrupt();
}
void Max_Limit_Reached()
{
  Max_Interrupt();
}
