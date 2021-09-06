#ifndef APP_FUNCTIONS_H_
#define APP_FUNCTIONS_H_

#define Initialize()    pinMode(DIR_FOR,OUTPUT);\
                        pinMode(DIR_BACK,OUTPUT);\
                        pinMode(MOTOR_SPEED,OUTPUT);\
                        pinMode(FOR_LED,OUTPUT);\
                        pinMode(BACK_LED,OUTPUT);\
                        pinMode(STOP_LED,OUTPUT)

#define Forward()	      Motor_ForwardDirection(DIR_FOR,DIR_BACK);\
                        LED_Forward(FOR_LED,BACK_LED,STOP_LED);\
                        dir_flag=FORWARD

#define Backward()      Motor_BackwardDirection(DIR_FOR,DIR_BACK);\
                        LED_Backward(FOR_LED,BACK_LED,STOP_LED);\
                        dir_flag=BACKWARD

#define Low_Speed_Op()  Time = Calculate_Time(abs(DiffAngle),MOTOR_LOW_SPEED,GEARBOX_RATIO);\
                        TotalTime+=Time;\
                        Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);\
                        Motor_SetSpeed(MOTOR_SPEED,Speed);\
                        delay(Time);\
                        Motor_Stop(DIR_FOR,DIR_BACK,MOTOR_SPEED);\
                        LED_Stop(FOR_LED,BACK_LED,STOP_LED);\
                        speed_flag=LOW_SPEED_OP                      

#define Accelerating()  Time = Calculate_Time(DEC_ANGLE,MOTOR_LOW_SPEED,GEARBOX_RATIO);\
                        TotalTime+=Time;\
                        Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);\
                        Motor_SetSpeed(MOTOR_SPEED,Speed);\
                        delay(Time)

#define High_Speed_Op() DiffAngle = abs(DiffAngle)-2*DEC_ANGLE;\
                        Time = Calculate_Time(DiffAngle,MOTOR_HIGH_SPEED,GEARBOX_RATIO);\
                        TotalTime+=Time;\
                        Speed = Calculate_Speed(HIGH_SPEED_VOLTAGE);\
                        Motor_SetSpeed(MOTOR_SPEED,Speed);\
                        delay(Time)

#define Decelerating()  Time = Calculate_Time(DEC_ANGLE,MOTOR_LOW_SPEED,GEARBOX_RATIO);\
                        TotalTime+=Time;\
                        Speed = Calculate_Speed(LOW_SPEED_VOLTAGE);\
                        Motor_SetSpeed(MOTOR_SPEED,Speed);\
                        delay(Time)

#define Stop()          Motor_Stop(DIR_FOR,DIR_BACK,MOTOR_SPEED);\
                        LED_Stop(FOR_LED,BACK_LED,STOP_LED)

#define Serial_Print()  Serial.println((src_flag==APP)? "Mobile Application Mode":"LabView GUI Mode");\
                        delay(LABVIEW_DELAY);\
                        Serial.print("Angle=");\
                        Serial.println(FinalAngle);\
                        delay(LABVIEW_DELAY);\
                        Serial.println((dir_flag==FORWARD)? "Forward":"Backward");\
                        delay(LABVIEW_DELAY);\
                        Serial.println((speed_flag==LOW_SPEED_OP)? "Low Speed":"High Speed");\
                        delay(LABVIEW_DELAY);\
                        Serial.print("Time=");\
                        Serial.println(TotalTime);\
                        delay(LABVIEW_DELAY);\
                        TotalTime=0

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
