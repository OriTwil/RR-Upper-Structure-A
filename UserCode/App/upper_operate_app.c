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

#define READY_TO_FIRE ((ReadChassisPoint(&Chassis_state) == Seventh_Point) || (ReadChassisPoint(&Chassis_state) == Fifth_Point) || (ReadChassisPoint(&Chassis_state) == Sixth_Point)) && (ReadUpperState(&Upper_state) != Hug)
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

        vTaskDelay(100);
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
    Upper_state.Pickup_ring  = Fifth_Ring;
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

struct
{
    int id;
    uint32_t last_tick;
    uint32_t button_min_time;
} BUTTON_JOYSTICK_R = {
    .button_min_time = 600,
    .id              = 0,
    .last_tick       = 0};

void JoystickControl()
{
    vPortEnterCritical();
    mavlink_joystick_air_t msg_joystick_air_temp = msg_joystick_air;
    vPortExitCritical();

    // 抱环
    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_JoystickR)) {
        /* code */
        if (BUTTON_JOYSTICK_R.last_tick + BUTTON_JOYSTICK_R.button_min_time < xTaskGetTickCount()) {
            BUTTON_JOYSTICK_R.last_tick = xTaskGetTickCount();
            if (BUTTON_JOYSTICK_R.id == 0) {
                BUTTON_JOYSTICK_R.id = 1;
                PickupSwitchState(Hug, &Upper_state);
            } else {
                BUTTON_JOYSTICK_R.id = 0;
                PickupSwitchState(HugBack, &Upper_state);
            }
        }
    }

    // 射环
    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_JoystickL) && READY_TO_FIRE) {
        PickupSwitchState(Pickup, &Upper_state);
    }

    // 底盘位置
    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_Btn4)) {
        PointSwitchNumber(First_Point, &Chassis_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_Btn5)) {
        PointSwitchNumber(Second_Point, &Chassis_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_RightCrossUp)) {
        PointSwitchNumber(Third_Point, &Chassis_state);
        // FireSwitchNumber(First_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_RightCrossLeft)) {
        PointSwitchNumber(Fourth_Point, &Chassis_state);
        // FireSwitchNumber(Third_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_RightCrossMid)) {
        PointSwitchNumber(Fifth_Point, &Chassis_state);
        // FireSwitchNumber(Third_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_RightCrossRight)) {
        PointSwitchNumber(Sixth_Point, &Chassis_state);
        // FireSwitchNumber(Third_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_RightCrossDown)) {
        PointSwitchNumber(Seventh_Point, &Chassis_state);
        // FireSwitchNumber(Third_Target, &Upper_state);
    }

    // 目标柱子
    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_LeftCrossUp)) {
        FireSwitchNumber(First_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_LeftCrossRight)) {
        FireSwitchNumber(Second_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_LeftCrossMid)) {
        FireSwitchNumber(Third_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_LeftCrossLeft)) {
        FireSwitchNumber(Fourth_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_LeftCrossDown)) {
        FireSwitchNumber(Fifth_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_Btn0)) {
        FireSwitchNumber(Sixth_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_Btn1)) {
        FireSwitchNumber(Seventh_Target, &Upper_state);
    }

    if (ReadJoystickButtons(msg_joystick_air_temp, Btn_Btn2)) {
        FireSwitchNumber(Eighth_Target, &Upper_state);
    }

    // 微调
    FireMicroAdjustment(&Fire_ref);
}