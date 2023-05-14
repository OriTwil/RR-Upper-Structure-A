/*
 * @Author: szf
 * @Date: 2023-05-11 16:08:17
 * @LastEditTime: 2023-05-14 23:23:30
 * @LastEditors: szf
 * @Description: 任务控制
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_state_management.c
 * @WeChat:szf13373959031
 */
#include "upper_state_management.h"

// 上层机构整体状态
UPPER_STATE Upper_state =
{
    .Pickup_state = Ready,
    .Pickup_step  = Overturn,
    .Pickup_ring  = First_Ring,
    .Fire_number  = First_Target,
};

// 取环组件的伺服值
SERVO_REF_PICKUP Pickup_ref =
{
    .position_servo_ref_arm   = 0,
    .position_servo_ref_pitch = 0,
    .position_servo_ref_yaw   = 0,
    .pwm_ccr_left             = 0,
    .pwm_ccr_middle           = 0,
    .pwm_ccr_right            = 0,
};

// 射环组件的伺服值
SERVO_REF_FIRE Fire_ref =
{
    .position_servo_ref_push = 0,
    .speed_servo_ref_left    = 0,
    .speed_servo_ref_right   = 0,
};

// 暂时没用
Button button =
{
    .button_min_time = 500,
    .last_tick       = 0,
};

/**
 * @brief 状态调整线程，根据遥控器、传感器等设计控制逻辑
 *
 * @param (void const *) argument
 * @return
 */
void StateManagemantTask(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    osDelay(20);
    for (;;) {
        osDelayUntil(&PreviousWakeTime, 5);
    }
}

/**
 * @brief 创建状态调整线程
 *
 * @param (void)
 * @return
 */
void StateManagemanttaskStart()
{

    osThreadDef(statemanagement, StateManagemantTask, osPriorityNormal, 0, 512);
    osThreadCreate(osThread(statemanagement), NULL);
}

/**
 * @brief 切换取环状态(	Ready,Pickup,Fire )
 *
 * @param (PICKUP_STATE) target_pick_up_state
 * @param (UPPER_STATE *) current_upper_state
 * @return
 */
void PickupSwitchState(PICKUP_STATE target_pick_up_state, UPPER_STATE *current_upper_state)
{
    xSemaphoreTake(current_upper_state->xMutex_upper, (TickType_t)10);
    current_upper_state->Pickup_state = target_pick_up_state;
    xSemaphoreGive(current_upper_state->xMutex_upper);
}

/**
 * @brief 切换取环所在步骤(	Overturn,Clamp,Overturn_back,Release )
 *
 */
void PickupSwitchStep(PICKUP_STEP target_pick_up_step, UPPER_STATE *current_upper_state)
{
    xSemaphoreTake(current_upper_state->xMutex_upper, (TickType_t)10);
    current_upper_state->Pickup_step = target_pick_up_step;
    xSemaphoreGive(current_upper_state->xMutex_upper);
}

/**
 * @brief 切换取环目标(1 2 3 4 5)
 *
 */
void PickupSwitchRing(PICKUP_RING target_pick_up_Ring, UPPER_STATE *current_upper_state)
{
    xSemaphoreTake(current_upper_state->xMutex_upper, (TickType_t)10);
    current_upper_state->Pickup_ring = target_pick_up_Ring;
    xSemaphoreGive(current_upper_state->xMutex_upper);
}

/**
 * @brief 切换射环的目标
 *
 */
void FireSwitchNumber(FIRE_NUMBER target_fire_number, UPPER_STATE *current_upper_state)
{
    xSemaphoreTake(current_upper_state->xMutex_upper, (TickType_t)10);
    current_upper_state->Fire_number = target_fire_number;
    xSemaphoreGive(current_upper_state->xMutex_upper);
}

/**
 * @brief 设置取环组件各电机伺服值
 *
 */
void SetServoRefPickup(float ref_pitch, float ref_yaw, float ref_arm, SERVO_REF_PICKUP *current_pickup_ref)
{
    xSemaphoreTake(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
    current_pickup_ref->position_servo_ref_pitch = ref_pitch;
    current_pickup_ref->position_servo_ref_yaw   = ref_yaw;
    current_pickup_ref->position_servo_ref_arm   = ref_arm;
    xSemaphoreGive(current_pickup_ref->xMutex_servo_pickup);
}

/**
 * @brief 设置舵机比较值，控制舵机角度
 *
 */
void SetPwmCcr(int pwm_ccr_left, int pwm_ccr_right, int pwm_ccr_middle, SERVO_REF_PICKUP *current_pickup_ref)
{
    xSemaphoreTake(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
    current_pickup_ref->pwm_ccr_left   = pwm_ccr_left;
    current_pickup_ref->pwm_ccr_right  = pwm_ccr_right;
    current_pickup_ref->pwm_ccr_middle = pwm_ccr_middle;
    xSemaphoreGive(current_pickup_ref->xMutex_servo_pickup);
}

/**
 * @brief 设置摩擦轮速度
 *
 */
void SetServoRefFire(float ref_left, float ref_right, SERVO_REF_FIRE *current_fire_ref)
{
    xSemaphoreTake(current_fire_ref->xMutex_servo_fire, (TickType_t)10);
    current_fire_ref->speed_servo_ref_left  = ref_left;
    current_fire_ref->speed_servo_ref_right = ref_right;
    xSemaphoreGive(current_fire_ref->xMutex_servo_fire);
}

/**
 * @brief 推环
 *
 */
void SetServoRefPush(float ref_push, SERVO_REF_FIRE *current_fire_ref)
{
    xSemaphoreTake(current_fire_ref->xMutex_servo_fire, (TickType_t)10);
    current_fire_ref->position_servo_ref_push = ref_push;
    xSemaphoreGive(current_fire_ref->xMutex_servo_fire);
}

/**
 * @brief 切换爪子夹紧/张开
 *
 */
void SetPwmCcrMiddle(int pwm_ccr_middle, SERVO_REF_PICKUP *current_pickup_ref)
{
    xSemaphoreTake(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
    current_pickup_ref->pwm_ccr_middle = pwm_ccr_middle;
    xSemaphoreGive(current_pickup_ref->xMutex_servo_pickup);
}