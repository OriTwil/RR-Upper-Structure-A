/*
 * @Author: szf
 * @Date: 2023-04-02 00:49:59
 * @LastEditTime: 2023-04-30 19:38:59
 * @LastEditors: szf
 * @Description: 射环线程
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\fire.c
 * @WeChat:szf13373959031
 */
#include "fire.h"

void FireTask(void const *argument)
{
    for(;;)
    {
        osDelay(20);
    } 
}

void FireTestTask(void const *argument)
{
    osDelay(20);
    
    for(;;)
    {
        if(Pickup_mode == Release || Pickup_mode == Fire || Pickup_state == Finished)
        {
            speedServo(5000,&hDJI[0]);
            speedServo(-5000,&hDJI[1]);
        }
        else
        {
            speedServo(0,&hDJI[0]);
            speedServo(0,&hDJI[1]);
        }

        
        CanTransmit_DJI_1234(&hcan1,
        hDJI[0].speedPID.output,
        hDJI[1].speedPID.output,
        hDJI[2].speedPID.output,
        hDJI[3].speedPID.output);
        osDelay(1);
    }
}

void FireTaskStart(mavlink_controller_t *controldata)
{
    // osThreadDef(fire, FireTask, osPriorityBelowNormal, 0, 512);
    // osThreadCreate(osThread(fire), controldata);

    osThreadDef(fire_test, FireTestTask, osPriorityBelowNormal, 0, 512);
    osThreadCreate(osThread(fire_test), NULL);
}