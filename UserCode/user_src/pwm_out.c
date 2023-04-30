/*
 * @Author: szf
 * @Date: 2023-04-28 22:40:58
 * @LastEditTime: 2023-04-30 19:02:09
 * @LastEditors: szf
 * @Description: 
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\pwm_out.c
 * @WeChat:szf13373959031
 **/

#include "pwm_out.h"

void PWMTask(void const *argument)
{
    osDelay(20);
    for (;;) {
        if (Pickup_state == Finished) {
            __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,1700); //
            __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,1070);
            __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1070);
        }
        else if (Pickup_state == Ongoing) // 开始取环
        {
            switch (Pickup_mode) {
                case Motionless:
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,600); //
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,1070);
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1070);
                    break;
                case Overturn:
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,600); //
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,550);
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1600);
                    break;
                case Clamp:
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,1700); //
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,550);
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1600);
                    break;
                case Pitch_Overturn_back:
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,1700); //
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,550);
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1600);
                    break;
                case Arm_Overturn_back:
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,1700); //
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,1070);
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1070);
                    break;
                case Release:
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,600); //
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,1070);
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1070);
                    break;
                case Fire:
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,600); //
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,1070);
                    __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1070);
                    break;
            }
        }
        osDelay(1);
    }
}

void PWMTestTask(void const *argument)
{
    osDelay(2);
    for (;;) {
        // static int n_ = 0;
        // if (n_++ > 100) {
        //     n_ = 0;
        //     HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_11); // A板上的绿灯
        // }
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,600); // 600张开1650夹紧
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,550);  // 550取环 1070放环
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1600); // 1600取环 1070放环

        // static int a=500;
        // static int mark=0;
        // if(mark==0){
        //     __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,a);
        //     __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,3000-a);
        //     a++;
        //     osDelay(2);
        //     if(a>=2499){
        //         mark=1;
        //     }
    // 
        //     if(mark==1){
        //     __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,a);
        //     __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,3000-a);
        //     a--;
        //     osDelay(2);
        //     if(a<=500){
        //         mark=0;
        //     }
        //     }  
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