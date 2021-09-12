#ifndef MODULES_H_
#define MODULES_H_

#define DIR_FOR               6     //Pin for forward direction
#define DIR_BACK              7     //Pin for backward direction
#define MOTOR_SPEED           5     //PWM pin for speed control
#define MIN_VOLTAGE           -3    //Required voltage for low speed
#define MAX_VOLTAGE           3     //Required voltage for high speed
#define INTERRUPT_ID1         0     //External interrupt pin1
#define INTERRUPT_ID2         1     //External interrupt pin2
#define MIN_ANGLE            -168   //Minimum angle 
#define MAX_ANGLE             168   //Maximum angle
#define FOR_LED               12    //Indication for forward direction
#define BACK_LED              13    //Indication for backward direction
#define STOP_LED              11    //Indication for stopping motor
#define RX                    9     //RX for bluetooth module
#define TX                    10    //TX for bluetooth module 
#define NEGATIVE_SIGN         45    //ASCII code for negative sign
#define POSITIVE_SIGN         43    //ASCII code for positive sign

//Motor Functions
void Motor_ForwardDirection(void);
void Motor_BackwardDirection(void);
void Motor_SetSpeed(int Speed);
void Motor_Stop(void);

//LED Functions
void LED_Forward(void);
void LED_Backward(void);
void LED_Stop(void);

//Direction Functions
void Forward(void);
void Backward(void);
void Stop(void);

//Initialization Function
void Init(void);

//Encoder Functions
double Encoder_Read(void);

//Calculate Functions
int Calculate_Speed(int Voltage);

//Serial Print Function
void Serial_Print(int cAngle,int dAngle, int Out);

#endif
