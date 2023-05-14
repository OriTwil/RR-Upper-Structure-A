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

void ServoTaskPlanA(void const *argument)
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
						switch(Upper_state.Pickup_ring)
						{
							case First_Ring:
								break;
							case Second_Ring:
								break;
							case Third_Ring:
								break;
							case Fourth_Ring:
								break;
							case Fifth_Ring:
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

void ServoTaskPlanB(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    osDelay(20);
    for(;;)
    {
        speedServo(Fire_ref.speed_servo_ref_left,&hDJI[0]);
        speedServo(Fire_ref.speed_servo_ref_right,&hDJI[1]);
        positionServo(Fire_ref.position_servo_ref_push,&hDJI[2]);

        positionServo(Pickup_ref.position_servo_ref_pitch, &hDJI[4]);
        positionServo(Pickup_ref.position_servo_ref_arm, &hDJI[5]);
        positionServo(Pickup_ref.position_servo_ref_yaw, &hDJI[6]);

        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,Pickup_ref.pwm_ccr_left);
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,Pickup_ref.pwm_ccr_right);
        __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,Pickup_ref.pwm_ccr_middle);  

        CanTransmit_DJI_5678(&hcan1,
        hDJI[4].speedPID.output,
        hDJI[5].speedPID.output,
        hDJI[6].speedPID.output,
        hDJI[7].speedPID.output);
		
        CanTransmit_DJI_1234(&hcan1,
        hDJI[0].speedPID.output,
        hDJI[1].speedPID.output,
        hDJI[2].speedPID.output,
        hDJI[3].speedPID.output);

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
    // osThreadDef(servo_plan_a, ServoTaskPlanA, osPriorityBelowNormal, 0, 512);
    // osThreadCreate(osThread(servo_plan_a), NULL);

    // osThreadDef(servo_plan_b, ServoTaskPlanB, osPriorityBelowNormal, 0, 512);
    // osThreadCreate(osThread(servo_plan_b), NULL);

    osThreadDef(servo_test,ServoTestTask,osPriorityBelowNormal,0,512);
    osThreadCreate(osThread(servo_test),NULL);
}


