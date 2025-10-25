#include "main.h" 
#include "menu.h"
#include "OLED.h"
#include "PID.h"
#include <string.h>
static uint8_t page = 1;
static uint8_t debug_index = 1;

uint8_t Limit_Index(uint8_t index, uint8_t min, uint8_t max) 
{
    if (index > max) {
        index = min;
    } else if (index < min) {
        index = max;
    }
    return index;
}

void Menu_Init(void)
{
    OLED_ShowString(1, 7, "Menu");
    OLED_ShowString(2, 2, "Speed");
    OLED_ShowString(3, 2, "MPU6050");
    OLED_ShowString(4, 2, "PID");

    OLED_ShowChar(2, 1, '>');
}

void Menu_ShowHome(uint8_t num)
{
    static uint8_t index = 2;
    static bool first_in = true;
    if (first_in) {
        OLED_Clear(); 
        Menu_ShowTarget(index);
        first_in = false;
    }

    OLED_ShowString(1, 7, "Menu");
    OLED_ShowString(2, 2, "Speed");
    OLED_ShowString(3, 2, "MPU6050");
    OLED_ShowString(4, 2, "PID");

    if (num == 2) {
        index--;
        index = Limit_Index(index, 2, 4);
        Menu_ShowTarget(index);
    } else if (num == 3) {
        index++;
        index = Limit_Index(index, 2, 4);
        Menu_ShowTarget(index);
    } else if (num == 4) {
        level++;
        first_in = true;
        page = index - 1;
    }
}

void Menu_Page1(uint8_t num)
{
    static bool first_in = true;
    if (first_in) {
        OLED_Clear();
        first_in = false;
    }

    OLED_ShowString(1, 6, "Speed");
    
    OLED_ShowString(2, 1, "L:"), OLED_ShowSignedNum(2, 3, L_speed, 3);
    OLED_ShowString(3, 1, "R:"), OLED_ShowSignedNum(3, 3, R_speed, 3);  
    OLED_ShowString(4, 1, ">Back");

    if (num == 4) {
        first_in = true;
        level--;
    }
}

void Menu_Page2(uint8_t num)
{ 
    static bool first_in = true;
    if (first_in) {
        OLED_Clear();
        first_in = false;
    }
    /*OLED_ShowSignedNum(1, 1, MPU6050.Acc_X, 4), OLED_ShowSignedNum(1, 6, MPU6050.Gyro_X, 4);
    OLED_ShowSignedNum(2, 1, MPU6050.Acc_Y, 4), OLED_ShowSignedNum(2, 6, MPU6050.Gyro_Y, 4);
    OLED_ShowSignedNum(3, 1, MPU6050.Acc_Z, 4), OLED_ShowSignedNum(3, 6, MPU6050.Gyro_Z, 4);*/

    OLED_ShowString(1, 1, "Pithc:"), OLED_ShowSignedFloat(1, 7, pitch, 4);
    OLED_ShowString(2, 1, "Roll:"), OLED_ShowSignedFloat(2, 7, roll, 4);
    OLED_ShowString(3, 1, "Yaw:"), OLED_ShowSignedFloat(3, 7, yaw, 4);
    OLED_ShowString(4, 1, ">Back");

    if (num == 4) {
        first_in = true;
        level--;
    }
}

void Menu_Page3(uint8_t num)
{
    static uint8_t index = 1;
    static bool first_in = true;
    if (first_in) {
        index = 1;
        OLED_Clear();
        Menu_ShowTarget(index);
        first_in = false;
    }

    OLED_ShowString(1, 2, "P:"), OLED_ShowFloat(1, 7, P_A, 3);
    OLED_ShowString(2, 2, "I:"), OLED_ShowFloat(2, 7, I_A, 3);
    OLED_ShowString(3, 2, "D:"), OLED_ShowFloat(3, 7, D_A, 3);

    OLED_ShowString(4, 2, "Back");

    if (!debug_flag) {
        if (num == 2) {                 //limit range
            index--;
            index = Limit_Index(index, 1, 4);
            Menu_ShowTarget(index);
        } else if (num == 3) {
            index++;
            index = Limit_Index(index, 1, 4);
            Menu_ShowTarget(index);
        }
    }
    if (num == 4 && index == 4) {           //Bcak to the home
        level--;
        first_in = true;
    } else if (num == 4 && index == 1) {    //Start debug
        debug_flag = !debug_flag;
        level++;
        debug_index = index;
    } else if (num == 4 && index == 2) {
        debug_flag = !debug_flag;
        level++;
        debug_index = index;
    } else if (num == 4 && index == 3) {
        debug_flag = !debug_flag;
        level++;
        debug_index = index;
    }
}

void Menu_ShowTarget(uint8_t index)
{
    switch (index) {
    case 1:
        OLED_ShowChar(1, 1, '>');
        OLED_ShowChar(2, 1, ' ');
        OLED_ShowChar(3, 1, ' ');
        OLED_ShowChar(4, 1, ' ');
        break;
    case 2:
        OLED_ShowChar(1, 1, ' ');
        OLED_ShowChar(2, 1, '>');
        OLED_ShowChar(3, 1, ' ');
        OLED_ShowChar(4, 1, ' ');
        break;
    case 3:
        OLED_ShowChar(1, 1, ' ');
        OLED_ShowChar(2, 1, ' ');
        OLED_ShowChar(3, 1, '>');
        OLED_ShowChar(4, 1, ' ');
        break;
    case 4:
        OLED_ShowChar(1, 1, ' ');
        OLED_ShowChar(2, 1, ' ');
        OLED_ShowChar(3, 1, ' ');
        OLED_ShowChar(4, 1, '>');
        break;
    default:
        OLED_ShowChar(1, 1, ' ');
        OLED_ShowChar(2, 1, ' ');
        OLED_ShowChar(3, 1, ' ');
        OLED_ShowChar(4, 1, ' ');
        break;
    }
}

void Menu_ShowInfor(uint8_t num)
{
    switch (page) 
    {
        case 1:
            Menu_Page1(num);
            break;
        case 2:
            Menu_Page2(num);
            break;
        case 3:
            Menu_Page3(num);
            break;
        default:
            Menu_Init();
            break;
    }
}

void Menu_Debug(uint8_t num, uint8_t index)
{
    switch (index)
    {
        case 1:
            PID_Set_P(num);
            break;
        case 2:
            PID_Set_I(num);
            break;
        case 3:
            PID_Set_D(num);
            break;
        default:
            break;
    }
} 

void Menu_Main(uint8_t num)
{   
    switch (level)
    {
        case 1:
            Menu_ShowHome(num);
            break;
        case 2:
            Menu_ShowInfor(num);
            break;
        case 3:
            Menu_Debug(num, debug_index);
            break;
        default:
            Menu_Init();
            break;
    }
}

