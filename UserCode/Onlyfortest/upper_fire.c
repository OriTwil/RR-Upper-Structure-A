/*
 * @Author: szf
 * @Date: 2023-04-02 00:49:59
 * @LastEditTime: 2023-05-14 22:53:33
 * @LastEditors: szf
 * @Description: 弃用，并入state_machine,现在用于射环测试
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_fire.c
 * @WeChat:szf13373959031
 */
#include "upper_fire.h"

/**
 * @description: 弃用
 * @author: szf
 * @return {void}
 */
void FireTask(void const *argument)
{
    for(;;)
    {
        
        osDelay(20);
    } 
}

/**
 * @description: 测试射环/电机
 * @author: szf
 * @return {void}
 */
void FireTestTask(void const *argument)
{
    osDelay(20);

    for(;;)
    {
        if(Raw_Data.right == 1)
        {
            speedServo(5000,&hDJI[0]);
            speedServo(-5000,&hDJI[1]);
        }
        else if(Raw_Data.right == 3)
        {
            speedServo(4000,&hDJI[0]);
            speedServo(-4000,&hDJI[1]);
        }
        else if(Raw_Data.right == 2)
        {
            speedServo(6000,&hDJI[0]);
            speedServo(-6000,&hDJI[1]);
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