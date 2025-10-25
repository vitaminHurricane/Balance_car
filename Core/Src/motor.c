#include "main.h"
#include "tim.h"
#include "motor.h"
#include "PID.h"

/*
 *	Lmotor -> GPIOA(Pin_2 & Pin_3)  2 -> go  3 -> back  B0 -> pwm
 *  Rmotor -> GPIOA(Pin_4 & Pin_5)  4 -> go  5 -> back  B1 -> pwm
 *
 */

float Limit_Speed(float speed)
{
	if (speed < 0) {
		speed = 0;
	} else if (speed > 1000) {
		speed = 1000;
	}
	return speed;
}

void Motor_SetSpeed(Motor motor, float speed)
{
	if (motor == Lmotor) {
		if (speed >= 0) {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, Limit_Speed(speed));
		} else {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, Limit_Speed(-speed));
		}
	} else if (motor == Rmotor) {
		if (speed >= 0) {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, Limit_Speed(speed));
		} else {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, Limit_Speed(-speed));
		}
	}
}

void Motor_Stop(void)
{ 
	Motor_SetSpeed(Lmotor, 0);
	Motor_SetSpeed(Rmotor, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void Motor_Test(void)
{
	Motor_SetSpeed(Lmotor, 1000);
	Motor_SetSpeed(Rmotor, 1000);
	HAL_Delay(500);
	if (start_flag == false) { return; }
	
	Motor_SetSpeed(Lmotor, 0);
	Motor_SetSpeed(Rmotor, 0);
	HAL_Delay(1000);
	if (start_flag == false) { return; }
	
	Motor_SetSpeed(Lmotor, -1000);
	Motor_SetSpeed(Rmotor, -1000);
	HAL_Delay(500);
	if (start_flag == false) { return; }
	
	Motor_SetSpeed(Lmotor, 0);
	Motor_SetSpeed(Rmotor, 0);
	HAL_Delay(1000);
	if (start_flag == false) { return; }
}

void Motor_control(void)                //no PID
{
	if (pitch > 0) {
		if (pitch < 18 && pitch > 3) {
			Motor_SetSpeed(Lmotor, (pitch - 3) * 4);
			Motor_SetSpeed(Rmotor, (pitch - 3) * 4);
		} else if (pitch < 33 && pitch > 18) {
			Motor_SetSpeed(Lmotor, 30 + (pitch - 3) * 2);
			Motor_SetSpeed(Rmotor, 30 + (pitch - 3) * 2);          
		} else {
			Motor_Stop();
		}
	} else if (pitch < 0) {
		if (pitch < 3 && pitch > -12) {
			Motor_SetSpeed(Lmotor, (pitch + 3) * 4);
			Motor_SetSpeed(Rmotor, (pitch + 3) * 4);    
		} else if (pitch < -12 && pitch > -27) {
			Motor_SetSpeed(Lmotor, -30 + (pitch + 3) * 2);
			Motor_SetSpeed(Rmotor, -30 + (pitch + 3) * 2);             
		} else {
			Motor_Stop();
		}
	}
}


