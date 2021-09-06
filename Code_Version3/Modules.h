#ifndef MODULES_H_
#define MODULES_H_

#define DIR_FOR               6     //Pin for forward direction
#define DIR_BACK              7     //Pin for backward direction
#define MOTOR_SPEED           5     //PWM pin for speed control
#define THRESHOLD_ANGLE       40    //Threshold angle for determining low and high speed
#define DEC_ANGLE             10     //The angle of decelerating at high speed
#define GEARBOX_RATIO         100   //Gear box ratio
#define MOTOR_LOW_SPEED       136   //RPM at low speed
#define MOTOR_HIGH_SPEED      415   //RPM at high speed
#define LOW_SPEED_VOLTAGE     1     //Required voltage for low speed
#define HIGH_SPEED_VOLTAGE    3     //Required voltage for high speed
#define INTERRUPT_ID1         0     //External interrupt pin1
#define INTERRUPT_ID2         1     //External interrupt pin2
#define MIN_ANGLE            -168   //Minimum angle 
#define MAX_ANGLE             168   //Maximum angle
#define LOW_SPEED_OP          false //Indication for low speed operation
#define HIGH_SPEED_OP         true  //Indication for high speed operation
#define FORWARD               true  //Indication for forward direction
#define BACKWARD              false //Indication for backward direction
#define APP                   false //Indication for getting data from mobile application
#define GUI                   true  //Indication for getting data from LabView
#define LABVIEW_DELAY         300   //Delay Time to be able to send to labview without losing data
#define FOR_LED               12    //Indication for forward direction
#define BACK_LED              13    //Indication for backward direction
#define STOP_LED              11    //Indication for stopping motor
#define RX                    9     //RX for bluetooth module
#define TX                    10    //TX for bluetooth module


//Motor Functions
void Motor_ForwardDirection(int ForwardPin,int BackwardPin);
void Motor_BackwardDirection(int ForwardPin,int BackwardPin);
void Motor_SetSpeed(int SpeedPin,int Speed);
void Motor_Stop(int ForwardPin,int BackwardPin,int SpeedPin);

//LED Functions
void LED_Forward(int ForwardInd,int BackwardInd,int StopInd);
void LED_Backward(int ForwardInd,int BackwardInd,int StopInd);
void LED_Stop(int ForwardInd,int BackwardInd,int StopInd);

//Calculate Functions
int Calculate_Time(int Angle,int Speed,int Gear);
int Calculate_Speed(int Voltage);

#endif
