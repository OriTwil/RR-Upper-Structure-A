/*
 * @Author: szf
 * @Date: 2023-03-11 12:51:38
 * @LastEditTime: 2023-05-11 19:34:58
 * @LastEditors: szf
 * @Description: 以固定频率进行伺服
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_servo.c
 * @WeChat:szf13373959031
 */

#include "upper_servo.h"
#include "user_config.h"
#include "upper_state_management.h"

float step_pitch = 0;
float step_arm = 0;
float step_pitch_back = 0;
float step_arm_back = 0;
float step_arm_fire = 0;

void ServoTask(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    osDelay(20);
    for (;;) 
    {
        switch(Upper_state.Pickup_state)
		{
			case Ready:
				// 锁死在初始状态
				break;
			case Pickup:
				// 开始取环
				switch(Upper_state.Pickup_step)
				{
					case Overturn:
						switch(Upper_state.Pickup_point)
						{
							case First_Point:
								break;
							case Second_Point:
								break;
							case Third_Point:
								break;
							case Fourth_Point:
								break;
							case Fifth_Point:
                                positionServo(step_pitch, &hDJI[4]);
                                step_pitch += 0.1;
                                if(step_pitch >= Overturn_Pitch)
                                {
                                    step_pitch = Overturn_Pitch;
                                }
                                positionServo(step_arm, &hDJI[5]);
                                step_arm -= 0.2;
                                if(step_arm <= Overture_Arm) 
                                {
                                    step_arm = Overture_Arm;
                                } 
                                positionServo(0, &hDJI[6]);
                                __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,600); //
                                __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,550);
                                __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1600);
								break;
							default:
								break;
						}
						break;
					case Clamp:
                        positionServo(Overturn_Pitch, &hDJI[4]);
                        positionServo(Overture_Arm, &hDJI[5]);
                        positionServo(0, &hDJI[6]);
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,1700); //
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,550);
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1600);
						break;
					case Pitch_Overturn_back:
                        positionServo(Overturn_Pitch + step_pitch_back, &hDJI[4]);
                        step_pitch_back -= 0.1;
                        if(step_pitch_back <= Overture_Pitch_back - Overturn_Pitch) 
                        {
                            step_pitch_back = Overture_Pitch_back - Overturn_Pitch;
                        }
                        positionServo(Overture_Arm, &hDJI[5]);
                        positionServo(0, &hDJI[6]);
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,1700); //
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,550);
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1600);
						break;
					case Arm_Overturn_back:
                        positionServo(Overture_Pitch_back, &hDJI[4]);
                        positionServo(Overture_Arm + step_arm_back, &hDJI[5]);
                        step_arm_back += 0.2;
                        if(step_arm_back > Overturn_Arm_back - Overture_Arm)
                        {
                            step_arm_back = Overturn_Arm_back - Overture_Arm;
                        }
                        positionServo(0, &hDJI[6]);
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,1700); //
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,1070);
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1070);
						break;
					case Release:
                        positionServo(Overture_Pitch_back, &hDJI[4]);
                        positionServo(Overturn_Arm_back, &hDJI[5]);
                        positionServo(0, &hDJI[6]);
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,600); //
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,1070);
                        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,1070);
						break;
					default:
						break;
				}
				break;
			case Fire:
				// 射环
				break;
			default:
				break;
		}
        osDelayUntil(&PreviousWakeTime, 3);
    }
}

void ServoTestTask(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    osDelay(20);
    for(;;)
    {
        positionServo(120, &hDJI[4]);
        positionServo(0, &hDJI[5]);
        positionServo(0, &hDJI[6]);  
        osDelayUntil(&PreviousWakeTime, 5);
    }
}


void ServoTaskStart(mavlink_controller_t *controldata)
{
    // osThreadDef(servo, ServoTask, osPriorityBelowNormal, 0, 512);
    // osThreadCreate(osThread(servo), NULL);

    osThreadDef(servo_test,ServoTestTask,osPriorityBelowNormal,0,512);
    osThreadCreate(osThread(servo_test),NULL);
}


