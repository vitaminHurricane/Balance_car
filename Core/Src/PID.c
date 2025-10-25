#include "main.h"
#include "OLED.h"
#include "PID.h"
#include "motor.h"

float P = 120, I = 0, D = 0;
float err_cur_l = 0, err_pre_l = 0, err_int_l = 0; 
float err_cur_r = 0, err_pre_r = 0, err_int_r = 0;

float P_A = 73, I_A = 4, D_A = 500;
float err0 = 0, err1 = 0, err_int = 0;

//P_A = 50, I_A = 4, D_A = 500;     前进

void PID_Set_P(uint8_t num)
{
    static bool first_in = true;
    if (first_in) {
        OLED_ShowChar(1, 5, '-');
        OLED_ShowChar(1, 13, '+');
        first_in = false;
    }
    
    OLED_ShowFloat(1, 7, P_A, 3);
    if (num == 2) {
        P_A -= 2;
    } else if (num == 3) {
        P_A += 2;
    }
    if (num == 4 && !first_in) {
        OLED_ShowChar(1, 5, ' ');
        OLED_ShowChar(1, 13, ' ');
        first_in = true;
        debug_flag = !debug_flag;
        level--;
    }    
}

void PID_Set_I(uint8_t num)
{
    static bool first_in = true;
    if (first_in) {
        OLED_ShowChar(2, 5, '-');
        OLED_ShowChar(2, 13, '+');
        first_in = false;
    }
    
    OLED_ShowFloat(2, 7, I_A, 3);
    if (num == 2) {
        I_A -= 0.5;
    } else if (num == 3) {
        I_A += 0.5;
    }
    if (num == 4 && !first_in) {
        OLED_ShowChar(2, 5, ' ');
        OLED_ShowChar(2, 13, ' ');
        first_in = true;
        debug_flag = !debug_flag;
        level--;
    }  
}

void PID_Set_D(uint8_t num)
{
    static bool first_in = true;
    if (first_in) {
        OLED_ShowChar(3, 5, '-');
        OLED_ShowChar(3, 13, '+');
        first_in = false;
    }
    
    OLED_ShowFloat(3, 7, D_A, 3);
    if (num == 2) {
        D_A -= 2;
    } else if (num == 3) {
        D_A += 2;
    }
    if (num == 4 && !first_in) {
        OLED_ShowChar(3, 5, ' ');
        OLED_ShowChar(3, 13, ' ');
        first_in = true;
        debug_flag = !debug_flag;
        level--;
    } 
}

float PID_Control(float aim, Motor direct)
{
    float actual, out;
    if (direct == Lmotor) {
        actual = L_speed;
        err_pre_l = err_cur_l;
        err_cur_l = aim - actual;
        err_int_l += err_cur_l;

        out = P * err_cur_l + I * err_int_l + D * (err_cur_l - err_pre_l);

        return out;
    } else {
        actual = R_speed;

        err_pre_r = err_cur_r;
        err_cur_r = aim - actual;
        err_int_r += err_cur_r;

        out = P * err_cur_r + I * err_int_r + D * (err_cur_r - err_pre_r);

        return out;
    }
}

void PID_Clear(void)
{
    err_cur_l = err_pre_l = err_int_l = 0;
    err_cur_r = err_pre_r = err_int_r = 0;
    err0 = err1 = err_int = 0;

}

void PID_Balance(float aim)                   //front is "+", beside is "-"
{
    float out;

    err1 = err0;
    err0 = aim - pitch;
    err_int += err0;
    
    if (err_int > MAX_Int) {
        err_int = MAX_Int;
    } else if (err_int < -MAX_Int) {
        err_int = -MAX_Int;
    }

    out = -P_A * err0 - I_A * err_int - D_A * (err0 - err1);

    if (out > MAX_Out) {
        out = MAX_Out;
    } else if (out < -MAX_Out) {
        out = -MAX_Out;
    }

    target_l = out;
    if (out > 0) {
        out += 30;
    } else if (out < 0) {
        out -= 30;
    }
    target_r = out;
}
