#include "main.h"
#include "MENU.h"
#include "OLED.h"
#include "tim.h"
#include <stdbool.h>

bool Key_GetStatu(uint16_t GPIO_Pin)
{
	bool statu = HAL_GPIO_ReadPin(GPIOA, GPIO_Pin);
	return !statu;
}

uint8_t Key_ActionPan(void)
{
	static bool pre1 = false, pre2 = false, pre3 = false, pre4 = false;
	static bool cur1 = false, cur2 = false, cur3 = false, cur4 = false;

	pre1 = cur1, pre2 = cur2, pre3 = cur3, pre4 = cur4;
	cur1 = Key_GetStatu(GPIO_PIN_12);
	cur2 = Key_GetStatu(GPIO_PIN_11);
	cur3 = Key_GetStatu(GPIO_PIN_10);
	cur4 = Key_GetStatu(GPIO_PIN_9);

	if (pre1 == false && cur1 == true) {
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		start_flag = !start_flag;
		return 1;
	} 
	if (pre2 == false && cur2 == true) {      //up row
		return 2;
	} 
	if (pre3 == false && cur3 == true) {      //down row
		return 3;
	} 
	if (pre4 == false && cur4 == true) { 	 //confirm
		return 4;
	}
	return 0;            						    //return 0 illustrate no action
}

