#ifndef __PID_H
#define __PID_H
#include "motor.h"
#define MAX_Int 200
#define MAX_Out 1000

extern float P, I, D;
extern float P_A, I_A, D_A;

void PID_Set_P(uint8_t num);
void PID_Set_I(uint8_t num);
void PID_Set_D(uint8_t num);
float PID_Control(float aim, Motor direct);
void PID_Balance(float aim);
void PID_Clear(void);

#endif

