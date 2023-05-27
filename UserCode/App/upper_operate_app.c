/*
 * @Author: szf
 * @Date: 2023-05-11 16:08:17
 * @LastEditTime: 2023-05-15 14:38:05
 * @LastEditors: szf
 * @Description: 任务控制
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_operate_app.c
 * @WeChat:szf13373959031
 */
#include "upper_operate_app.h"
#include "user_config.h"
#include "semphr.h"
#include "upper_communicate.h"
#include "math.h"
#include "upper_commen.h"

// 暂时没用
Button button =
    {
        .button_min_time = 500,
        .last_tick       = 0,
};

/**
 * @brief 状态调整线程，根据遥控器、传感器等设计控制逻辑
 * @todo 设计操作手操作逻辑
 * @param (void const *) argument
 * @return
 */
void StateManagemantTask(void const *argument)
{
    osDelay(20);
    for (;;) {

        // SetServoRefPickupTrajectory(0, 0, 195, &Pickup_ref);
        // SetPwmCcrMiddleTrajectory(1200,&Pickup_ref);
        // SetPwmCcr(1950,1200,1300,&Pickup_ref);
        // SetServoRefFire

        // todo 检测到操作手按对应柱子的按钮(可以用信号量？)
        // vPortEnterCritical();
        // if(Raw_Data.left == 3)
        // {
        SetPwmCcrMiddle(1900, &Pickup_ref);
        // SetServoRefPickupTrajectory(-60,0,-30,&Pickup_ref);
        // vTaskDelay(100);
        // SetServoRefFire(4000,-4000,&Fire_ref);
        // vTaskDelay(5000);
        // SetServoRefPush(70,&Fire_ref);
        // vTaskDelay(1000);
        // SetServoRefPush(0,&Fire_ref);
        // }
        // vPortExitCritical();

        vTaskDelay(10);
    }
}

/**
 * @brief 创建状态调整线程
 *
 * @param (void)
 * @return
 */
void StateManagemantTaskStart()
{

    osThreadDef(statemanagement, StateManagemantTask, osPriorityNormal, 0, 512);
    osThreadCreate(osThread(statemanagement), NULL);
    // xTaskCreate(osThread(statemanagement),NULL);
}

/**
 * @brief 初始化函数
 *
 * @param (void)
 * @bug Motor好像没什么用
 */
void UpperStateInit()
{
    // 互斥锁
    Upper_state.xMutex_upper       = xSemaphoreCreateMutex();
    Pickup_ref.xMutex_servo_pickup = xSemaphoreCreateMutex();
    Fire_ref.xMutex_servo_fire     = xSemaphoreCreateMutex();

    // 上层机构整体状态
    Upper_state.Pickup_state = Ready;
    Upper_state.Pickup_step  = Overturn;
    Upper_state.Pickup_ring  = First_Ring;
    Upper_state.Fire_number  = First_Target;

    // 取环组件的伺服值
    Pickup_ref.position_servo_ref_arm   = 0;
    Pickup_ref.position_servo_ref_pitch = 0;
    Pickup_ref.position_servo_ref_yaw   = 0;
    Pickup_ref.pwm_ccr_left             = 0;
    Pickup_ref.pwm_ccr_middle           = CCR_Middle_Closed;
    Pickup_ref.pwm_ccr_right            = 0;

    // 射环组件的伺服值
    Fire_ref.position_servo_ref_push = 0;
    Fire_ref.speed_servo_ref_left    = 0;
    Fire_ref.speed_servo_ref_right   = 0;
}
