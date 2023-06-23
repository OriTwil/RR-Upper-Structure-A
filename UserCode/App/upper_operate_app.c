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
#include <semphr.h>
#include "upper_communicate.h"
#include "math.h"
#include "upper_commen.h"
#include "remote_control.h"
#include "upper_state_machine.h"

#define FIRE_POINT (Third_Point || Fourth_Point || Fifth_Point || Sixth_Point)
#define READY_TO_FIRE (ReadChassisPoint(&Chassis_state) == FIRE_POINT && ReadUpperState(&Upper_state) != Hug)
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
    vTaskDelay(20);
    PickupSwitchState(Ready, &Upper_state);
    vTaskDelay(1000);
    for (;;) {
        JoystickControl();

        vTaskDelay(80);
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

    osThreadDef(statemanagement, StateManagemantTask, osPriorityNormal, 0, 1024);
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
    Upper_state.xMutex_upper       = xSemaphoreCreateRecursiveMutex();
    Pickup_ref.xMutex_servo_pickup = xSemaphoreCreateRecursiveMutex();
    Fire_ref.xMutex_servo_fire     = xSemaphoreCreateRecursiveMutex();
    Chassis_state.xMutex_point     = xSemaphoreCreateRecursiveMutex();

    // 上层机构整体状态
    Upper_state.Pickup_state = Ready;
    Upper_state.Pickup_step  = Overturn;
    Upper_state.Pickup_ring  = Second_Ring;
    Upper_state.Fire_number  = First_Target;

    // 取环组件的伺服值
    Pickup_ref.position_servo_ref_arm   = 0;
    Pickup_ref.position_servo_ref_pitch = 0;
    Pickup_ref.position_servo_ref_yaw   = 0;
    Pickup_ref.pwm_ccr_left             = CCR_Left_Ready;
    Pickup_ref.pwm_ccr_middle           = CCR_Middle_Ready;
    Pickup_ref.pwm_ccr_right            = CCR_Right_Ready;

    // 射环组件的伺服值
    Fire_ref.position_servo_ref_push = 0;
    Fire_ref.speed_servo_ref_left    = 0;
    Fire_ref.speed_servo_ref_right   = 0;
}

void JoystickControl()
{
    // 抱环
    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn2) && ReadUpperState(&Upper_state) == Hug) {
        PickupSwitchState(HugBack, &Upper_state);
    }
    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn3) && ReadUpperState(&Upper_state) != Fire) {
        PickupSwitchState(HugBack, &Upper_state);
    }

    // 射环
    if (ReadJoystickButtons(msg_joystick_air, Btn_LeftCrossDown) && READY_TO_FIRE) {
        PickupSwitchRing(Fourth_Ring, &Upper_state);
        // FireSwitchNumber(First_Target, &Upper_state);
        PickupSwitchState(Pickup, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn0) && READY_TO_FIRE) {
        PickupSwitchRing(Fifth_Ring, &Upper_state);
        // FireSwitchNumber(First_Target, &Upper_state);
        PickupSwitchState(Pickup, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn1) && READY_TO_FIRE) {
        PickupSwitchRing(Sixth_Ring, &Upper_state);
        // FireSwitchNumber(First_Target, &Upper_state);
        PickupSwitchState(Pickup, &Upper_state);
    }

    // 底盘位置
    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn4)) {
        PointSwitchNumber(First_Point, &Chassis_state);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_Btn5)) {
        PointSwitchNumber(Second_Point, &Chassis_state);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossUp)) {
        PointSwitchNumber(Third_Point, &Chassis_state);
        FireSwitchNumber(First_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossLeft)) {
        PointSwitchNumber(Fourth_Point, &Chassis_state);
        FireSwitchNumber(Third_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossMid)) {
        PointSwitchNumber(Fifth_Point, &Chassis_state);
        FireSwitchNumber(Third_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossRight)) {
        PointSwitchNumber(Sixth_Point, &Chassis_state);
        FireSwitchNumber(Third_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air, Btn_RightCrossDown)) {
        PointSwitchNumber(Seventh_Point, &Chassis_state);
        FireSwitchNumber(Third_Target, &Upper_state);
    }
}