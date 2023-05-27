#ifndef __UPPER_COMMEN_H__
#define __UPPER_COMMEN_H__

// 取环步骤
typedef enum {
    Overturn,
    Clamp,
    Overturn_back,
    Release,
} PICKUP_STEP;
// 取环状态
typedef enum {
    Ready,
    Pickup,
    Fire
} PICKUP_STATE;

// 目标环
typedef enum {
    First_Ring = 1,
    Second_Ring,
    Third_Ring,
    Fourth_Ring,
    Fifth_Ring
} PICKUP_RING;

// 目标柱子
typedef enum {
    First_Target = 1,
    Second_Target,
    Third_Target,
    Fourth_Target,
    Fifth_Target
} FIRE_NUMBER;

// 上层机构整体
typedef __IO struct
{
    PICKUP_STATE Pickup_state;
    PICKUP_STEP Pickup_step;
    PICKUP_RING Pickup_ring;
    FIRE_NUMBER Fire_number;
    SemaphoreHandle_t xMutex_upper;
    DJI_t Motor[8];
} UPPER_STATE;

// 取环组件伺服参考值
typedef __IO struct
{
    float position_servo_ref_pitch;
    float position_servo_ref_yaw;
    float position_servo_ref_arm;
    int pwm_ccr_left;
    int pwm_ccr_right;
    int pwm_ccr_middle;
    SemaphoreHandle_t xMutex_servo_pickup;
} SERVO_REF_PICKUP;

// 射环组件伺服参考值
typedef __IO struct
{
    float speed_servo_ref_left;
    float speed_servo_ref_right;
    float position_servo_ref_push;
    SemaphoreHandle_t xMutex_servo_fire;
} SERVO_REF_FIRE;

// 按键
typedef __IO struct
{
    uint32_t last_tick;
    uint32_t button_min_time;
} Button;

#endif