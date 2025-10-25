#ifndef __Motor_H
#define __Motor_H
typedef enum motor {
	Lmotor,
	Rmotor,
}Motor;

typedef enum {
	car_go,
	car_back,
	car_stop,
}car_statu;

float Limit_Speed(float speed);
void Motor_SetSpeed(Motor motor, float speed);
void Motor_Stop(void);
void Motor_Test(void);
void Motor_control(void);

#endif

