/*
 * @Author: szf
 * @Date: 2023-05-11 16:08:17
 * @LastEditTime: 2023-05-15 14:38:05
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
 * @todo 设计操作手操作逻辑
 * @param (void const *) argument
 * @return
 */
void StateManagemantTask(void const *argument)
{
    UpperStateInit();
    uint32_t PreviousWakeTime = osKernelSysTick();
    osDelay(20);
    for (;;) {

        //todo 检测到操作手按对应柱子的按钮(可以用信号量？)
        // FireSwitchNumber
        // PickupSwitchStep
        // PickupSwitchState
        osDelayUntil(&PreviousWakeTime, 5);
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
    Upper_state.xMutex_upper = xSemaphoreCreateMutex(); 
    Pickup_ref.xMutex_servo_pickup = xSemaphoreCreateMutex();
    Fire_ref.xMutex_servo_fire = xSemaphoreCreateMutex();

    // 上层机构整体状态
    Upper_state.Pickup_state = Ready;
    Upper_state.Pickup_step  = Overturn;
    Upper_state.Pickup_ring  = First_Ring;
    Upper_state.Fire_number  = First_Target;

    vPortEnterCritical();
    for (int i = 0; i < 7; i++) {
        Upper_state.Motor[i] = hDJI[i];
    }
    vPortExitCritical();

    // 取环组件的伺服值
    Pickup_ref.position_servo_ref_arm   = 0;
    Pickup_ref.position_servo_ref_pitch = 0;
    Pickup_ref.position_servo_ref_yaw   = 0;
    Pickup_ref.pwm_ccr_left             = 0;
    Pickup_ref.pwm_ccr_middle           = 0;
    Pickup_ref.pwm_ccr_right            = 0;

    // 射环组件的伺服值
    Fire_ref.position_servo_ref_push = 0;
    Fire_ref.speed_servo_ref_left    = 0;
    Fire_ref.speed_servo_ref_right   = 0;
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
 * @brief 切换爪子夹紧/张开
 *
 */
void SetPwmCcrMiddle(int pwm_ccr_middle, SERVO_REF_PICKUP *current_pickup_ref)
{
    xSemaphoreTake(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
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
 * @brief T型速度规划函数
 * @param initialAngle 初始角度
 * @param maxAngularVelocity 最大角速度
 * @param AngularAcceleration 角加速度
 * @param targetAngle 目标角度
 * @param currentTime 当前时间
 * @param currentTime 当前角度
 * @todo 转换为国际单位制
 */
void VelocityPlanning(float initialAngle, float maxAngularVelocity, float AngularAcceleration, float targetAngle, float currentTime, float *currentAngle)
{

    float angleDifference = targetAngle - initialAngle;      // 计算到目标位置的角度差
    float sign            = (angleDifference >= 0) ? 1 : -1; // 判断角度差的正负(方向)

    float accelerationTime = maxAngularVelocity / AngularAcceleration;                                                      // 加速(减速)总时间
    float constTime        = (fabs(angleDifference) - AngularAcceleration * pow(accelerationTime, 2)) / maxAngularVelocity; // 匀速总时间
    float totalTime        = constTime + accelerationTime * 2;                                                              // 计算到达目标位置所需的总时间

    // 判断能否达到最大速度
    if (constTime > 0) {
        // 根据当前时间判断处于哪个阶段
        if (currentTime <= accelerationTime) {
            // 加速阶段
            *currentAngle = initialAngle + sign * 0.5 * AngularAcceleration * pow(currentTime, 2);
        } else if (currentTime <= accelerationTime + constTime) {
            // 匀速阶段
            *currentAngle = initialAngle + sign * maxAngularVelocity * (currentTime - accelerationTime) + 0.5 * sign * AngularAcceleration * pow(accelerationTime, 2);
        } else if (currentTime <= totalTime) {
            // 减速阶段
            float decelerationTime = currentTime - accelerationTime - constTime;
            *currentAngle          = initialAngle + sign * maxAngularVelocity * constTime + 0.5 * AngularAcceleration * pow(accelerationTime, 2) + sign * (maxAngularVelocity * decelerationTime - 0.5 * AngularAcceleration * pow(decelerationTime, 2));
        } else {
            // 达到目标位置
            *currentAngle = targetAngle;
        }
    } else {
        maxAngularVelocity = sqrt(fabs(angleDifference) * AngularAcceleration);
        accelerationTime   = maxAngularVelocity / AngularAcceleration;
        totalTime          = 2 * accelerationTime;
        constTime          = 0;
        // 根据当前时间判断处于哪个阶段
        if (currentTime <= accelerationTime) {
            // 加速阶段
            *currentAngle = initialAngle + sign * 0.5 * AngularAcceleration * pow(currentTime, 2);
        } else if (currentTime <= totalTime) {
            // 减速阶段
            float decelerationTime = currentTime - accelerationTime; // 减速时间
            *currentAngle          = initialAngle + sign * 0.5 * AngularAcceleration * pow(accelerationTime, 2) + sign * (maxAngularVelocity * decelerationTime - 0.5 * AngularAcceleration * pow(decelerationTime, 2));
        } else {
            // 达到目标位置
            *currentAngle = targetAngle;
        }
    }
}

/**
 * @brief 设置按轨迹规划的伺服参考值
 * @param float ref_pitch Pitch轴电机目标位置
 * @param float ref_yaw Yaw轴电机目标位置
 * @param float ref_arm Arm轴电机目标位置
 * @param SERVO_REF_PICKUP *current_pickup_ref
 * @todo 转换为国际单位制
 */
void SetServoRefPickupTrajectory(float ref_pitch, float ref_yaw, float ref_arm, SERVO_REF_PICKUP *current_pickup_ref)
{
    TickType_t startTime    = xTaskGetTickCount(); // 初始时间
    float initialAnglePitch = current_pickup_ref->position_servo_ref_pitch;
    float initialAngleArm   = current_pickup_ref->position_servo_ref_arm;
    float initialAngleYaw   = current_pickup_ref->position_servo_ref_yaw; // 电机初始位置

    bool isArrive          = false; // 标志是否达到目标位置
    double differencePitch = 0;
    double differenceArm   = 0;
    double differenceYaw   = 0; // 和目标之间的角度差

    do {
        TickType_t endTime     = xTaskGetTickCount();
        TickType_t elapsedTime = endTime - startTime;
        float timeSec          = (elapsedTime / (TickType_t)configTICK_RATE_HZ); // 获取当前时间/s

        xSemaphoreTake(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
        // 速度规划
        VelocityPlanning(initialAnglePitch, MaxAngularVelocity_Pitch, MotorAngularAcceleration, ref_pitch, timeSec, &(current_pickup_ref->position_servo_ref_pitch));
        VelocityPlanning(initialAngleYaw, MaxAngularVelocity_Yaw, MotorAngularAcceleration, ref_yaw, timeSec, &(current_pickup_ref->position_servo_ref_yaw));
        VelocityPlanning(initialAngleArm, MaxAngularVelocity_Arm, MotorAngularAcceleration, ref_arm, timeSec, &(current_pickup_ref->position_servo_ref_arm));
        xSemaphoreGive(current_pickup_ref->xMutex_servo_pickup);

        // 判断是否到达目标位置
        differencePitch = fabs(current_pickup_ref->position_servo_ref_pitch - ref_pitch);
        differenceArm   = fabs(current_pickup_ref->position_servo_ref_yaw - ref_yaw);
        differenceYaw   = fabs(current_pickup_ref->position_servo_ref_arm - ref_arm);
        if (differencePitch < 0.1 && differenceArm < 0.1 && differenceYaw < 0.1) {
            isArrive = true;
        }
        vTaskDelay(2);
    } while (!isArrive);
}
