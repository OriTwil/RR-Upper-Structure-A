/*
 * @Author: szf
 * @Date: 2023-04-28 22:40:58
 * @LastEditTime: 2023-05-13 16:10:21
 * @LastEditors: szf
 * @Description: 弃用，并入Servo线程，现在用于测试舵机
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_pwm_out.c
 * @WeChat:szf13373959031
 **/

#include "upper_pwm_out.h"

void PWMTask(void const *argument)
{
    osDelay(20);
    for (;;) {
        osDelay(1);
    }
}

void PWMTestTask(void const *argument)
{
    osDelay(2);
    for (;;) 
    {
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,1000); // 600张开1650夹紧
        // __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,550);  // 550取环 1070放环
        // __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1600); // 1600取环 1070放环

        // static int a=500;
        // static int mark=0;
        
        // if(mark==0)
        // {
        //     __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,a);
        //     __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,3000-a);
        //     a++;
        //     osDelay(2);
        //     if(a>=2499)
        //     {
        //         mark=1;
        //     }
        // }
        // if(mark==1)
        // {
        //     __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,a);
        //     __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,3000-a);
        //     a--;
        //     osDelay(2);
        //     if(a<=500)
        //     {
        //         mark=0;
        //     }
        // }
        osDelay(2); 
    }  
}

void PWMTaskStart(mavlink_controller_t *controldata)
{
    // osThreadDef(pwm, PWMTask, osPriorityBelowNormal, 0, 512);
    // osThreadCreate(osThread(pwm), NULL);

    osThreadDef(pwm_test, PWMTestTask, osPriorityBelowNormal, 0, 512);
    osThreadCreate(osThread(pwm_test), NULL);
}