#include <SoftwareSerial.h>         //Including SoftwareSerial library to connect with bluetooth module
#include "Modules.h"                //Including the defined library 'Modules'
#include "PID_v1.h"                 //Including the defined library 'PID_v1.h'

//Define Variables we'll be connecting to
double DesiredAngle=0, CurrentAngle=0, Output,DiffAngle;

//Specify the links and initial tuning parameters
double Kp=2, Ki=0.001, Kd=0;

//Creating object from PID library
PID myPID(&CurrentAngle, &Output, &DesiredAngle, Kp, Ki, Kd, DIRECT);

//Bluetooth module for Mobile Application
SoftwareSerial mySerial(RX, TX);

//Declaration of global variables
String inputString = "";        //Variable that holds the recieved string
bool stringComplete = false,PID_flag=false;    //Flag to indicate recieving of string from application or LabView

//ISRs for external interrupt
void Min_Limit_Reached();
void Max_Limit_Reached();

void setup() {
  //Initalizing needed pins as output
  Init();

  //Attaching interrupts at pins 0&1
  attachInterrupt(INTERRUPT_ID1,Min_Limit_Reached,RISING);
  attachInterrupt(INTERRUPT_ID2,Max_Limit_Reached,RISING);

  //Initalizing software serial connection
  mySerial.begin(9600);
  myPID.SetMode(AUTOMATIC);   //Turning on PID
  myPID.SetOutputLimits(Calculate_Speed(MIN_VOLTAGE), Calculate_Speed(MAX_VOLTAGE));  //Setting Limits for the output
}

void loop() {
  //Checking data from applcation
   if(mySerial.available())
  {
    inputString=mySerial.readString();
    stringComplete=true;  //Flag to indicate the completion of the string
  }
  if (stringComplete) //Checking for flag
  {
    DesiredAngle = inputString.toInt();     //Converting to integer
    inputString = "";                       //Clearing string
    stringComplete = false;                 //Clearing Flag
    PID_flag=true;                          //Setting flag to enter loop
    while(PID_flag==true)
    {
      CurrentAngle = Encoder_Read();            //Updating current angle using encoder
      DiffAngle = DesiredAngle - CurrentAngle;
      //Determining direction according to the difference
      if(DiffAngle>0)
      {
        Forward();
      }
      else if(DiffAngle<0)
      {
        Backward();
      }
      myPID.Compute();                          //Calculating error to determine output using PID
      Motor_SetSpeed(abs(Output));  //Setting mootor speed according to calculated output
      Serial_Print(CurrentAngle, DiffAngle, Output);
      if(abs(Output)==0)
      {
        LED_Stop();
        PID_flag=false;
      }
    }
  }
}

//For read from write buffer
void serialEvent() 
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();   //Reading character from serial
    if (inChar == '#')                   //Checking for stop bit '#'
    {
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
  Output=0;
  CurrentAngle=MIN_ANGLE;
  PID_flag=false;
}
//ISR when reaching maximum limit
void Max_Limit_Reached()
{
  Serial.println("Max Interrupt");
  Motor_Stop();
  LED_Stop();
  Output=0;
  CurrentAngle=MAX_ANGLE;
  PID_flag=false;
}
