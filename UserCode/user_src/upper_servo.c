/*
 * @Author: szf
 * @Date: 2023-03-11 12:51:38
 * @LastEditTime: 2023-05-14 23:35:31
 * @LastEditors: szf
 * @Description: 以固定频率进行伺服
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_servo.c
 * @WeChat:szf13373959031
 */

#include "upper_servo.h"
#include "user_config.h"
#include "upper_state_management.h"

/**
 * @description: 伺服线程，六个电机和两个舵机
 * @author: szf
 * @return {void}
 */
void ServoTask(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    osDelay(20);
    for (;;) {
        // 射环两个电机、推环电机伺服
        xSemaphoreTake(Fire_ref.xMutex_servo_fire, (TickType_t)10);
        speedServo(Fire_ref.speed_servo_ref_left, &hDJI[Motor_id_Fire_Left]);
        speedServo(Fire_ref.speed_servo_ref_right, &hDJI[Motor_id_Fire_Right]);
        positionServo(Fire_ref.position_servo_ref_push, &hDJI[Motor_id_Push]);
        xSemaphoreGive(Fire_ref.xMutex_servo_fire);

        // Pitch、Arm、Yaw轴电机的伺服
        xSemaphoreTake(Pickup_ref.xMutex_servo_pickup, (TickType_t)10);
        positionServo(Pickup_ref.position_servo_ref_pitch, &hDJI[Motor_id_Pitch]);
        positionServo(Pickup_ref.position_servo_ref_arm, &hDJI[Motor_id_Arm]);
        positionServo(Pickup_ref.position_servo_ref_yaw, &hDJI[Motor_id_Yaw]);

        // 爪子三个舵机的伺服
        __HAL_TIM_SetCompare(&htim_claw_left, TIM_CHANNEL_CLAW_LEFT, Pickup_ref.pwm_ccr_left);
        __HAL_TIM_SetCompare(&htim_claw_right, TIM_CHANNEL_CLAW_RIGHT, Pickup_ref.pwm_ccr_right);
        __HAL_TIM_SetCompare(&htim_claw_middle, TIM_CHANNEL_CLAW_MIDDLE, Pickup_ref.pwm_ccr_middle);
        xSemaphoreGive(Pickup_ref.xMutex_servo_pickup);

        CanTransmit_DJI_1234(&hcan1,
                             hDJI[0].speedPID.output,
                             hDJI[1].speedPID.output,
                             hDJI[2].speedPID.output,
                             hDJI[3].speedPID.output);

        CanTransmit_DJI_5678(&hcan1,
                             hDJI[4].speedPID.output,
                             hDJI[5].speedPID.output,
                             hDJI[6].speedPID.output,
                             hDJI[7].speedPID.output);

        osDelayUntil(&PreviousWakeTime, 2);
    }
}

void ServoTestTask(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    osDelay(20);
    for (;;) {
        positionServo(120, &hDJI[4]);
        positionServo(0, &hDJI[5]);
        positionServo(0, &hDJI[6]);
        osDelayUntil(&PreviousWakeTime, 5);
    }
}

void ServoTaskStart(mavlink_controller_t *controldata)
{
    osThreadDef(servo, ServoTask, osPriorityBelowNormal, 0, 512);
    osThreadCreate(osThread(servo), NULL);

    // osThreadDef(servo_test,ServoTestTask,osPriorityBelowNormal,0,512);
    // osThreadCreate(osThread(servo_test),NULL);
}

// 电机初始化
void MotorInit()
{
    CANFilterInit(&hcan1);
    hDJI[Motor_id_Fire_Left].motorType  = M3508; // 射环左
    hDJI[Motor_id_Fire_Right].motorType = M3508; // 射环右
    hDJI[Motor_id_Push].motorType       = M2006; // 推环
    hDJI[Motor_id_Pitch].motorType      = M3508; // Pitch
    hDJI[Motor_id_Arm].motorType        = M3508; // Arm
    hDJI[Motor_id_Yaw].motorType        = M3508; // Yaw

    DJI_Init(); // 大疆电机初始化
}

// 舵机PWM初始化
void PWMInit()
{
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
}