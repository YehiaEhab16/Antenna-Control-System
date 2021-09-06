#ifndef APP_FUNCTIONS_H_
#define APP_FUNCTIONS_H_

#define Initialize()    pinMode(DIR_FOR,OUTPUT);\
                        pinMode(DIR_BACK,OUTPUT);\
                        pinMode(MOTOR_SPEED,OUTPUT);\
                        pinMode(FOR_LED,OUTPUT);\
                        pinMode(BACK_LED,OUTPUT);\
                        pinMode(STOP_LED,OUTPUT)

#define Forward()	      Serial.println("Forward");\
                        Motor_ForwardDirection(DIR_FOR,DIR_BACK);\
                        LED_Forward(FOR_LED,BACK_LED,STOP_LED)

#define Backward()      Serial.println("Backward");\
                        Motor_BackwardDirection(DIR_FOR,DIR_BACK);\
                        LED_Backward(FOR_LED,BACK_LED,STOP_LED)

#define Low_Speed_Op()  Serial.println("LOW SPEED");\
                        Time = Calculate_Time(abs(DiffAngle),MOTOR_LOW_SPEED,GEARBOX_RATIO);\
                        Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);\
                        Motor_SetSpeed(MOTOR_SPEED,Speed);\
                        Serial.print("Time=");\
                        Serial.println(Time);\
                        delay(Time);\
                        Motor_Stop(DIR_FOR,DIR_BACK,MOTOR_SPEED);\
                        LED_Stop(FOR_LED,BACK_LED,STOP_LED);\
                        Serial.println("STOP MOTOR")

#define Accelerating()  Time = Calculate_Time(DEC_ANGLE,MOTOR_LOW_SPEED,GEARBOX_RATIO);\
                        Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);\
                        Motor_SetSpeed(MOTOR_SPEED,Speed);\
                        Serial.print("Angle1=");\
                        Serial.println(DEC_ANGLE);\
                        Serial.print("Time1=");\
                        Serial.println(Time);\
                        delay(Time)

#define High_Speed_Op() DiffAngle = abs(DiffAngle)-2*DEC_ANGLE;\
                        Time = Calculate_Time(DiffAngle,MOTOR_HIGH_SPEED,GEARBOX_RATIO);\
                        Speed = Calculate_Speed(HIGH_SPEED_VOLTAGE);\
                        Motor_SetSpeed(MOTOR_SPEED,Speed);\
                        Serial.print("Angle2=");\
                        Serial.println(DiffAngle);\
                        Serial.print("Time2=");\
                        Serial.println(Time);\
                        delay(Time)

#define Decelerating()  Time = Calculate_Time(DEC_ANGLE,MOTOR_LOW_SPEED,GEARBOX_RATIO);\
                        Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);\
                        Motor_SetSpeed(MOTOR_SPEED,Speed);\
                        Serial.print("Angle3=");\
                        Serial.println(DEC_ANGLE);\
                        Serial.print("Time3=");\
                        Serial.println(Time);\
                        delay(Time)

#define Stop()          Motor_Stop(DIR_FOR,DIR_BACK,MOTOR_SPEED);\
                        LED_Stop(FOR_LED,BACK_LED,STOP_LED);\
                        Serial.println("STOP MOTOR")

#define Min_Interrupt() Serial.println("Min Interrupt");\
                        Motor_Stop(DIR_FOR,DIR_BACK,MOTOR_SPEED);\
                        LED_Stop(FOR_LED,BACK_LED,STOP_LED);\
                        Serial.println("STOP MOTOR");\
                        DiffAngle=0;\
                        Speed=0;\
                        Time=0;\
                        DesiredAngle=MIN_ANGLE

#define Max_Interrupt() Serial.println("Max Interrupt");\
                        Motor_Stop(DIR_FOR,DIR_BACK,MOTOR_SPEED);\
                        LED_Stop(FOR_LED,BACK_LED,STOP_LED);\
                        Serial.println("STOP MOTOR");\
                        DiffAngle=0;\
                        Speed=0;\
                        Time=0;\
                        DesiredAngle=MAX_ANGLE

#endif
