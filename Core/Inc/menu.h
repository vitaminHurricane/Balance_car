#ifndef __MENU_H
#define __MENU_H

uint8_t Limit_Index(uint8_t index, uint8_t min, uint8_t max);
void Menu_Init(void);
void Menu_ShowTarget(uint8_t index);
void Menu_ShowInfor(uint8_t num);
void Menu_Debug(uint8_t num, uint8_t index);
void Menu_Main(uint8_t num);
void Menu_ShowHome(uint8_t num);
void Menu_Page1(uint8_t num);
void Menu_Page2(uint8_t num);
void Menu_Page3(uint8_t num);

#endif

