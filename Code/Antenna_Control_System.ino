#include "Modules.h"                //Including the defined library 'Modules'

#define DIR_FOR               4     //Pin for forward direction
#define DIR_BACK              5     //Pin for backward direction
#define MOTOR_SPEED           6     //PWM pin for speed control
#define THRESHOLD_ANGLE       10    //Threshold angle for determining low and high speed
#define DEC_ANGLE             5     //The angle of decelerating at high speed
#define GEARBOX_RATIO         100   //Gear box ratio
#define MOTOR_LOW_SPEED       136   //RPM at low speed
#define MOTOR_HIGH_SPEED      415   //RPM at high speed
#define LOW_SPEED_VOLTAGE     1     //Required voltage for low speed
#define HIGH_SPEED_VOLTAGE    3     //Required voltage for high speed
#define INTERRUPT_ID1         0     //External interrupt pin1
#define INTERRUPT_ID2         1     //External interrupt pin2
#define MIN_ANGLE            -168   //Minimum angle 
#define MAX_ANGLE             168   //Maximum angle
#define FOR_LED               11    //Indication for forward direction
#define BACK_LED              12    //Indication for backward direction
#define STOP_LED              13    //Indication for stopping motor

//ISR for external interrupt
void Min_Limit_Reached();
void Max_Limit_Reached();

//Declaration of global variables
int CurrentAngle=0,DesiredAngle,DiffAngle,Time,Speed;

void setup() {
  //Initalizing needed pins as output
  pinMode(DIR_FOR,OUTPUT);
  pinMode(DIR_BACK,OUTPUT);
  pinMode(MOTOR_SPEED,OUTPUT);
  attachInterrupt(INTERRUPT_ID1,Min_Limit_Reached,FALLING);
  attachInterrupt(INTERRUPT_ID2,Max_Limit_Reached,FALLING);

  Serial.begin(9600);               //Initalizing serial connection
}

void loop() {
  if(Serial.available())            //Checking for input from serial monitor
  {
    DesiredAngle = Serial.parseInt();//Reading desired angle
    DiffAngle = DesiredAngle - CurrentAngle;//Calculating difference between desired and current angle

    //Determining direction according to the difference
    if(DiffAngle>0)
    {
      Motor_ForwardDirection(DIR_FOR,DIR_BACK);
      LED_Foraward(FOR_LED,BACK_LED,STOP_LED);
    }
    else
    {
      Motor_BackwardDirection(DIR_FOR,DIR_BACK);
      LED_Backward(FOR_LED,BACK_LED,STOP_LED);
    }
      
    //Determining speed according to the difference
    //Case1: Low speed operation
    if(abs(DiffAngle)<THRESHOLD_ANGLE)
    {
      //Calculating speed and time
      Time = Calculate_Time(abs(DiffAngle),MOTOR_LOW_SPEED,GEARBOX_RATIO);
      Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);
      //Setting motor speed and operating it for the required interval of time and then stop the motor movement
      Motor_SetSpeed(MOTOR_SPEED,Speed);
      delay(Time);
      Motor_Stop(DIR_FOR,DIR_BACK,MOTOR_SPEED);
      LED_Stop(FOR_LED,BACK_LED,STOP_LED);
    }
    //Case2: High speed operation
    else
    {
      //The motor will first start at low speed for 5 degrees ,then it will continue with high speed until it reaches the last 5 degrees which will also be in low speed
      //Low speed interval
      if(DiffAngle!=0)
      {
        Time = Calculate_Time(DEC_ANGLE,MOTOR_LOW_SPEED,GEARBOX_RATIO);
        Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);
        Motor_SetSpeed(MOTOR_SPEED,Speed);
        delay(Time);
      }

      //High speed interval
      if(DiffAngle!=0)
      {
      DiffAngle = abs(DiffAngle)-2*DEC_ANGLE;
      Time = Calculate_Time(DiffAngle,MOTOR_HIGH_SPEED,GEARBOX_RATIO);
      Speed = Calculate_Speed(HIGH_SPEED_VOLTAGE);
      Motor_SetSpeed(MOTOR_SPEED,Speed);
      delay(Time);
      }

      //Low speed interval
      if(DiffAngle!=0)
      {
      Time = Calculate_Time(DEC_ANGLE,MOTOR_LOW_SPEED,GEARBOX_RATIO);
      Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);
      Motor_SetSpeed(MOTOR_SPEED,Speed);
      delay(Time);
      }
      Motor_Stop(DIR_FOR,DIR_BACK,MOTOR_SPEED);
      LED_Stop(FOR_LED,BACK_LED,STOP_LED);
    }
    CurrentAngle=DesiredAngle;    //Updating current angle after the operation
  }

}

void Min_Limit_Reached()
{
  Motor_Stop(DIR_FOR,DIR_BACK,MOTOR_SPEED);
  LED_Stop(FOR_LED,BACK_LED,STOP_LED);
  DiffAngle=0;
  Speed=0;
  Time=0;
  DesiredAngle=MIN_ANGLE;
}
void Max_Limit_Reached()
{
  Motor_Stop(DIR_FOR,DIR_BACK,MOTOR_SPEED);
  LED_Stop(FOR_LED,BACK_LED,STOP_LED);
  DiffAngle=0;
  Speed=0;
  Time=0;
  DesiredAngle=MAX_ANGLE;
}
