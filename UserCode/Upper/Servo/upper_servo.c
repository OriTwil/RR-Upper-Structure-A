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
#include "upper_commen.h"
#include "remote_control.h"

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
        .micro_adjust_ref        = 0,
};

ADJUSTMENT Adjustment;
/**
 * @description: 伺服线程，六个电机和两个舵机
 * @author: szf
 * @return {void}
 */
void ServoTask(void const *argument)
{
    uint32_t PreviousWakeTime = xTaskGetTickCount();
    vTaskDelay(20);
    for (;;) {

        // 射环两个电机、推环电机伺服
        xSemaphoreTakeRecursive(Fire_ref.xMutex_servo_fire, (TickType_t)10);
        speedServo((Fire_ref.speed_servo_ref_left - Fire_ref.micro_adjust_ref) * Fire_Wheel_Ratio, &hDJI[Motor_id_Fire_Left_Large]);
        speedServo(Fire_ref.speed_servo_ref_left - Fire_ref.micro_adjust_ref, &hDJI[Motor_id_Fire_Left_Small]);
        speedServo((Fire_ref.speed_servo_ref_right + Fire_ref.micro_adjust_ref) * Fire_Wheel_Ratio, &hDJI[Motor_id_Fire_Right_Large]);
        speedServo(Fire_ref.speed_servo_ref_right + Fire_ref.micro_adjust_ref, &hDJI[Motor_id_Fire_Right_Small]);
        positionServo(Fire_ref.position_servo_ref_push, &hDJI[Motor_id_Push]);
        xSemaphoreGiveRecursive(Fire_ref.xMutex_servo_fire);

        // Pitch、Arm、Yaw轴电机的伺服
        xSemaphoreTakeRecursive(Pickup_ref.xMutex_servo_pickup, (TickType_t)10);
        positionServo(Pickup_ref.position_servo_ref_pitch, &hDJI[Motor_id_Pitch]);
        positionServo(Pickup_ref.position_servo_ref_arm, &hDJI[Motor_id_Arm]);
        positionServo(Pickup_ref.position_servo_ref_yaw, &hDJI[Motor_id_Yaw]);

        // 爪子三个舵机的伺服
        __HAL_TIM_SetCompare(&htim_claw_left, TIM_CHANNEL_CLAW_LEFT, Pickup_ref.pwm_ccr_left);
        __HAL_TIM_SetCompare(&htim_claw_right, TIM_CHANNEL_CLAW_RIGHT, Pickup_ref.pwm_ccr_right);
        __HAL_TIM_SetCompare(&htim_claw_middle, TIM_CHANNEL_CLAW_MIDDLE, Pickup_ref.pwm_ccr_middle);
        xSemaphoreGiveRecursive(Pickup_ref.xMutex_servo_pickup);

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

        vTaskDelayUntil(&PreviousWakeTime, 2);
    }
}

void ServoTestTask(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    osDelay(20);
    for (;;) {
        // speedServo(1000, &hDJI[0]);
        // speedServo(1000, &hDJI[1]);
        CanTransmit_DJI_1234(&hcan1,
                             hDJI[0].speedPID.output,
                             hDJI[1].speedPID.output,
                             hDJI[2].speedPID.output,
                             hDJI[3].speedPID.output);
        osDelayUntil(&PreviousWakeTime, 2);
    }
}

void ServoTaskStart()
{
    osThreadDef(servo, ServoTask, osPriorityBelowNormal, 0, 1024);
    osThreadCreate(osThread(servo), NULL);

    // osThreadDef(servo_test, ServoTestTask, osPriorityBelowNormal, 0, 512);
    // osThreadCreate(osThread(servo_test), NULL);
}

// 电机初始化
void MotorInit()
{
    CANFilterInit(&hcan1);
    hDJI[Motor_id_Fire_Left_Large].motorType  = M3508; // 射环左大
    hDJI[Motor_id_Fire_Left_Small].motorType  = M3508; // 射环左小
    hDJI[Motor_id_Fire_Right_Large].motorType = M3508; // 射环右大
    hDJI[Motor_id_Fire_Right_Small].motorType = M3508; // 射环右小
    hDJI[Motor_id_Push].motorType             = M2006; // 推环
    hDJI[Motor_id_Pitch].motorType            = M3508; // Pitch
    hDJI[Motor_id_Arm].motorType              = M3508; // Arm
    hDJI[Motor_id_Yaw].motorType              = M3508; // Yaw

    DJI_Init(); // 大疆电机初始化
}

// 舵机PWM初始化
void PWMInit()
{
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
}

/**
 * @brief 设置取环组件各电机伺服值
 *
 */
void SetServoRefPickup(float ref_pitch, float ref_yaw, float ref_arm, SERVO_REF_PICKUP *current_pickup_ref)
{
    xSemaphoreTakeRecursive(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
    current_pickup_ref->position_servo_ref_pitch = ref_pitch;
    current_pickup_ref->position_servo_ref_yaw   = ref_yaw;
    current_pickup_ref->position_servo_ref_arm   = ref_arm;
    xSemaphoreGiveRecursive(current_pickup_ref->xMutex_servo_pickup);
}

/**
 * @brief 设置舵机比较值，控制舵机角度
 *
 */
void SetPwmCcr(int pwm_ccr_left, int pwm_ccr_right, int pwm_ccr_middle, SERVO_REF_PICKUP *current_pickup_ref)
{
    xSemaphoreTakeRecursive(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
    current_pickup_ref->pwm_ccr_left   = pwm_ccr_left;
    current_pickup_ref->pwm_ccr_right  = pwm_ccr_right;
    current_pickup_ref->pwm_ccr_middle = pwm_ccr_middle;
    xSemaphoreGiveRecursive(current_pickup_ref->xMutex_servo_pickup);
}

/**
 * @brief 切换爪子夹紧/张开
 *
 */
void SetPwmCcrMiddle(int pwm_ccr_middle, SERVO_REF_PICKUP *current_pickup_ref)
{
    xSemaphoreTakeRecursive(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
    current_pickup_ref->pwm_ccr_middle = pwm_ccr_middle;
    xSemaphoreGiveRecursive(current_pickup_ref->xMutex_servo_pickup);
}

/**
 * @brief 设置摩擦轮速度
 *
 */
void SetServoRefFire(float ref_left, float ref_right, SERVO_REF_FIRE *current_fire_ref)
{
    xSemaphoreTakeRecursive(current_fire_ref->xMutex_servo_fire, (TickType_t)10);
    current_fire_ref->speed_servo_ref_left  = ref_left;
    current_fire_ref->speed_servo_ref_right = ref_right;
    xSemaphoreGiveRecursive(current_fire_ref->xMutex_servo_fire);
}

/**
 * @brief 推环
 *
 */
void SetServoRefPush(float ref_push, SERVO_REF_FIRE *current_fire_ref)
{
    xSemaphoreTakeRecursive(current_fire_ref->xMutex_servo_fire, (TickType_t)10);
    current_fire_ref->position_servo_ref_push = ref_push;
    xSemaphoreGiveRecursive(current_fire_ref->xMutex_servo_fire);
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
void VelocityPlanning(float initialAngle, float maxAngularVelocity, float AngularAcceleration, float targetAngle, float currentTime, volatile float *currentAngle)
{

    float angleDifference = targetAngle - initialAngle;     // 计算到目标位置的角度差
    float sign            = (angleDifference > 0) ? 1 : -1; // 判断角度差的正负(方向)

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
            *currentAngle          = initialAngle + sign * maxAngularVelocity * constTime + 0.5 * sign * AngularAcceleration * pow(accelerationTime, 2) + sign * (maxAngularVelocity * decelerationTime - 0.5 * AngularAcceleration * pow(decelerationTime, 2));
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

void CcrUniform(int initialCcr, int maxCcrVelocity, int targetCcr, float currentTime, volatile int *currentCcr)
{
    int ccrDifference = targetCcr - initialCcr;
    int sign          = (ccrDifference > 0) ? 1 : (-1);
    float totalTime   = fabs(ccrDifference) / maxCcrVelocity;

    if (currentTime < totalTime) {
        *currentCcr = (int)(initialCcr + sign * maxCcrVelocity * currentTime);
    } else {
        *currentCcr = (int)targetCcr;
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

    float initialAnglePitch = current_pickup_ref->position_servo_ref_pitch;
    float initialAngleArm   = current_pickup_ref->position_servo_ref_arm;
    float initialAngleYaw   = current_pickup_ref->position_servo_ref_yaw; // 电机初始位置

    bool isArrive          = false; // 标志是否达到目标位置
    double differencePitch = 0;
    double differenceArm   = 0;
    double differenceYaw   = 0;                   // 和目标之间的角度差
    TickType_t startTime   = xTaskGetTickCount(); // 初始时间

    do {
        TickType_t endTime     = xTaskGetTickCount();
        TickType_t elapsedTime = endTime - startTime;
        float timeSec          = (elapsedTime / (1000.0)); // 获取当前时间/s

        xSemaphoreTakeRecursive(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
        // 速度规划
        VelocityPlanning(initialAnglePitch, MaxAngularVelocity_Pitch, MotorAngularAcceleration_Pitch, ref_pitch, timeSec, &(current_pickup_ref->position_servo_ref_pitch));
        VelocityPlanning(initialAngleYaw, MaxAngularVelocity_Yaw, MotorAngularAcceleration_Yaw, ref_yaw, timeSec, &(current_pickup_ref->position_servo_ref_yaw));
        VelocityPlanning(initialAngleArm, MaxAngularVelocity_Arm, MotorAngularAcceleration_Arm, ref_arm, timeSec, &(current_pickup_ref->position_servo_ref_arm));

        xSemaphoreGiveRecursive(current_pickup_ref->xMutex_servo_pickup);

        // 判断是否到达目标位置
        differencePitch = fabs(current_pickup_ref->position_servo_ref_pitch - ref_pitch);
        differenceYaw   = fabs(current_pickup_ref->position_servo_ref_yaw - ref_yaw);
        differenceArm   = fabs(current_pickup_ref->position_servo_ref_arm - ref_arm);
        if (differencePitch < 0.1 && differenceArm < 0.1 && differenceYaw < 0.1) {
            isArrive = true;
        }
        vTaskDelay(2);
    } while (!isArrive);
}

/**
 * @brief 速度规划所有取环电机、舵机
 * @param float ref_pitch Pitch轴电机目标位置
 * @param float ref_yaw Yaw轴电机目标位置
 * @param float ref_arm Arm轴电机目标位置
 * @param int ref_ccr_left
 * @param int ref_ccr_right
 * @param int ref_ccr_middle
 * @param SERVO_REF_PICKUP *current_pickup_ref
 * @todo 转换为国际单位制
 */
void SetAllPickupTrajectory(float ref_pitch,
                            float ref_yaw,
                            float ref_arm,
                            int ref_ccr_left,
                            int ref_ccr_right,
                            int ref_ccr_middle,
                            SERVO_REF_PICKUP *current_pickup_ref)
{

    float initialAnglePitch = current_pickup_ref->position_servo_ref_pitch;
    float initialAngleArm   = current_pickup_ref->position_servo_ref_arm;
    float initialAngleYaw   = current_pickup_ref->position_servo_ref_yaw; // 电机初始位置
    int initialCCRLeft      = current_pickup_ref->pwm_ccr_left;
    int initialCCRRight     = current_pickup_ref->pwm_ccr_right;
    int initialCCRMiddle    = current_pickup_ref->pwm_ccr_middle;

    bool isArrive           = false; // 标志是否达到目标位置
    double differencePitch  = 0;
    double differenceArm    = 0;
    double differenceYaw    = 0; // 和目标之间的角度差
    int differenceCcrLeft   = 0;
    int differenceCcrRight  = 0;
    int differenceCcrMiddle = 0;

    TickType_t startTime = xTaskGetTickCount(); // 初始时间

    do {
        TickType_t endTime     = xTaskGetTickCount();
        TickType_t elapsedTime = endTime - startTime;
        float timeSec          = (elapsedTime / (1000.0)); // 获取当前时间/s

        xSemaphoreTakeRecursive(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
        // 速度规划
        VelocityPlanning(initialAnglePitch, MaxAngularVelocity_Pitch, MotorAngularAcceleration_Pitch, ref_pitch, timeSec, &(current_pickup_ref->position_servo_ref_pitch));
        VelocityPlanning(initialAngleYaw, MaxAngularVelocity_Yaw, MotorAngularAcceleration_Yaw, ref_yaw, timeSec, &(current_pickup_ref->position_servo_ref_yaw));
        VelocityPlanning(initialAngleArm, MaxAngularVelocity_Arm, MotorAngularAcceleration_Arm, ref_arm, timeSec, &(current_pickup_ref->position_servo_ref_arm));

        CcrUniform(initialCCRLeft, MaxAngularVelocity_CCR, ref_ccr_left, timeSec, &(current_pickup_ref->pwm_ccr_left));
        CcrUniform(initialCCRRight, MaxAngularVelocity_CCR, ref_ccr_right, timeSec, &(current_pickup_ref->pwm_ccr_right));
        CcrUniform(initialCCRMiddle, MaxAngularVelocity_CCR, ref_ccr_middle, timeSec, &(current_pickup_ref->pwm_ccr_middle));
        xSemaphoreGiveRecursive(current_pickup_ref->xMutex_servo_pickup);

        // 判断是否到达目标位置
        differencePitch     = fabs(current_pickup_ref->position_servo_ref_pitch - ref_pitch);
        differenceYaw       = fabs(current_pickup_ref->position_servo_ref_yaw - ref_yaw);
        differenceArm       = fabs(current_pickup_ref->position_servo_ref_arm - ref_arm);
        differenceCcrLeft   = fabs(current_pickup_ref->pwm_ccr_left - ref_ccr_left);
        differenceCcrRight  = fabs(current_pickup_ref->pwm_ccr_right - ref_ccr_right);
        differenceCcrMiddle = fabs(current_pickup_ref->pwm_ccr_middle - ref_ccr_middle);
        if (differencePitch < 0.1 && differenceArm < 0.1 && differenceYaw < 0.1 && differenceCcrLeft < 2 && differenceCcrRight < 2 && differenceCcrMiddle < 2) {
            isArrive = true;
        }
        vTaskDelay(2);
    } while (!isArrive);
}

// 保证抱环收回时，不会碰到环
void SetAllHugBackTrajectory(float ref_pitch,
                             float ref_yaw,
                             float ref_arm,
                             int ref_ccr_left,
                             int ref_ccr_right,
                             int ref_ccr_middle,
                             SERVO_REF_PICKUP *current_pickup_ref)
{

    float initialAnglePitch = current_pickup_ref->position_servo_ref_pitch;
    float initialAngleArm   = current_pickup_ref->position_servo_ref_arm;
    float initialAngleYaw   = current_pickup_ref->position_servo_ref_yaw; // 电机初始位置
    int initialCCRLeft      = current_pickup_ref->pwm_ccr_left;
    int initialCCRRight     = current_pickup_ref->pwm_ccr_right;
    int initialCCRMiddle    = current_pickup_ref->pwm_ccr_middle;

    bool isArrive           = false; // 标志是否达到目标位置
    double differencePitch  = 0;
    double differenceArm    = 0;
    double differenceYaw    = 0; // 和目标之间的角度差
    int differenceCcrLeft   = 0;
    int differenceCcrRight  = 0;
    int differenceCcrMiddle = 0;

    TickType_t startTime = xTaskGetTickCount(); // 初始时间

    do {
        TickType_t endTime     = xTaskGetTickCount();
        TickType_t elapsedTime = endTime - startTime;
        float timeSec          = (elapsedTime / (1000.0)); // 获取当前时间/s

        xSemaphoreTakeRecursive(current_pickup_ref->xMutex_servo_pickup, (TickType_t)10);
        // 速度规划
        VelocityPlanning(initialAnglePitch, MaxAngularVelocity_Pitch, MotorAngularAcceleration_Pitch, ref_pitch, timeSec, &(current_pickup_ref->position_servo_ref_pitch));
        VelocityPlanning(initialAngleYaw, MaxAngularVelocity_Yaw, MotorAngularAcceleration_Yaw, ref_yaw, timeSec, &(current_pickup_ref->position_servo_ref_yaw));
        VelocityPlanning(initialAngleArm, MaxAngularVelocity_Arm, MotorAngularAcceleration_Arm, ref_arm, timeSec, &(current_pickup_ref->position_servo_ref_arm));

        if (timeSec > 0.4) {
            CcrUniform(initialCCRLeft, MaxAngularVelocity_CCR, ref_ccr_left, (timeSec - 0.4), &(current_pickup_ref->pwm_ccr_left));
            CcrUniform(initialCCRRight, MaxAngularVelocity_CCR, ref_ccr_right, (timeSec - 0.4), &(current_pickup_ref->pwm_ccr_right));
            CcrUniform(initialCCRMiddle, MaxAngularVelocity_CCR, ref_ccr_middle, (timeSec - 0.4), &(current_pickup_ref->pwm_ccr_middle));
        }
        xSemaphoreGiveRecursive(current_pickup_ref->xMutex_servo_pickup);

        // 判断是否到达目标位置
        differencePitch     = fabs(current_pickup_ref->position_servo_ref_pitch - ref_pitch);
        differenceYaw       = fabs(current_pickup_ref->position_servo_ref_yaw - ref_yaw);
        differenceArm       = fabs(current_pickup_ref->position_servo_ref_arm - ref_arm);
        differenceCcrLeft   = fabs(current_pickup_ref->pwm_ccr_left - ref_ccr_left);
        differenceCcrRight  = fabs(current_pickup_ref->pwm_ccr_right - ref_ccr_right);
        differenceCcrMiddle = fabs(current_pickup_ref->pwm_ccr_middle - ref_ccr_middle);
        if (differencePitch < 0.1 && differenceArm < 0.1 && differenceYaw < 0.1 && differenceCcrLeft < 2 && differenceCcrRight < 2 && differenceCcrMiddle < 2) {
            isArrive = true;
        }
        vTaskDelay(2);
    } while (!isArrive);
}

void FireMicroAdjustment(SERVO_REF_FIRE *current_fire_ref)
{

    xSemaphoreTake(current_fire_ref->xMutex_servo_fire, portMAX_DELAY);
    current_fire_ref->micro_adjust_ref = (float)ReadJoystickKnobsRight(msg_joystick_air);
    xSemaphoreGive(current_fire_ref->xMutex_servo_fire);
}