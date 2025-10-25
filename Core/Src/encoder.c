#include "main.h"
#include "motor.h"
#include "encoder.h"

/*
 *
 *  L_encoder  A6, A7
 *  R_encoder  B6, B7
 *
 */

void Encoder_Checklevel(void)
{
	pre_LA = cur_LA, pre_LB = cur_LB;
	cur_LA = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
	cur_LB = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
	
	pre_RA = cur_RA, pre_RB = cur_RB;
	cur_RA = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
	cur_RB = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7);
}

void Encoder_Softsimulation(void)
{
	Encoder_Checklevel();
	int8_t LA_Trigger = (int8_t)cur_LA - (int8_t)pre_LA;
	int8_t LB_Trigger = (int8_t)cur_LB - (int8_t)pre_LB;
	int8_t RA_Trigger = (int8_t)cur_RA - (int8_t)pre_RA;
	int8_t RB_Trigger = (int8_t)cur_RB - (int8_t)pre_RB;
	if ((cur_LB == 1 && LA_Trigger == 1) || (cur_LB == 0 && LA_Trigger == -1) || (cur_LA == 1 && LB_Trigger == -1) || (cur_LA == 0 && LB_Trigger == 1)) {
		L_loc += 1;
	} else if ((cur_LB == 1 && LA_Trigger == -1) || (cur_LB == 0 && LA_Trigger == 1) || (cur_LA == 1 && LB_Trigger == 1) || (cur_LA == 0 && LB_Trigger == -1)) {
		L_loc -= 1;
	}
	if ((cur_RB == 1 && RA_Trigger == -1) || (cur_RB == 0 && RA_Trigger == 1) || (cur_RA == 1 && RB_Trigger == 1) || (cur_RA == 0 && RB_Trigger == -1)) {
		R_loc += 1;
	} else if ((cur_RB == 1 && RA_Trigger == 1) || (cur_RB == 0 && RA_Trigger == -1) || (cur_RA == 1 && RB_Trigger == -1) || (cur_RA == 0 && RB_Trigger == 1)) {
		R_loc -= 1;
	}
}

int16_t Encoder_GetSpeed(Encoder direct)
{
	if (direct == L_encoder) {
		int16_t temp = L_loc;
		L_loc = 0;
		return temp;
	} else if (direct == R_encoder) {
		int16_t temp = R_loc;
		R_loc = 0;
		return temp;
	}
	return 0;
}
