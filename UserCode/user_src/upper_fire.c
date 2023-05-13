/*
 * @Author: szf
 * @Date: 2023-04-02 00:49:59
 * @LastEditTime: 2023-05-11 19:53:10
 * @LastEditors: szf
 * @Description: 射环线程
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_fire.c
 * @WeChat:szf13373959031
 */
#include "upper_fire.h"

void FireTask(void const *argument)
{
    for(;;)
    {
        switch(Upper_state.Pickup_point)
        {
            case First_Point:
                switch(Upper_state.Fire_number)
                {
                    case First_Target:
                        break;
                    case Second_Target:
                        break;
                    default:
                        break;
                }
                break;
            case Second_Point:
                switch(Upper_state.Fire_number)
                {
                    case Second_Target:
                        break;
                    case Third_Target:
                        break;
                    default:
                        break;
                }
                break;
            case Third_Point:
                switch(Upper_state.Fire_number)
                {
                    case Third_Target:
                        break;
                    case Fourth_Target:
                        break;
                    default:
                        break;
                }
                break;
            case Fourth_Point:
                switch(Upper_state.Fire_number)
                {
                    case Fourth_Target:
                        break;
                    case Fifth_Target:
                        break;
                    default:
                        break;
                }
                break;
            case Fifth_Point:
                switch(Upper_state.Fire_number)
                {
                    case Fourth_Target:
                        break;
                    case Fifth_Target:
                        break;
                    default:
                        break;
                }
                break;
        }
        osDelay(20);
    } 
}

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