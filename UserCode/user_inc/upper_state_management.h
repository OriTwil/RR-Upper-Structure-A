#ifndef UPPER_STATE_MANAGEMENT
#define UPPER_STATE_MANAGEMENT

#include "user_main.h"
#include "wtr_dji.h"
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

void UpperStateInit();

void StateManagemantTaskStart();

void PickupSwitchState(PICKUP_STATE target_pick_up_state, UPPER_STATE *current_upper_state);

void PickupSwitchStep(PICKUP_STEP target_pick_up_step, UPPER_STATE *current_upper_state);

void PickupSwitchRing(PICKUP_RING target_pick_up_Ring, UPPER_STATE *current_upper_state);

void FireSwitchNumber(FIRE_NUMBER target_fire_number, UPPER_STATE *current_upper_state);

void SetServoRefPickup(float ref_pitch, float ref_yaw, float ref_arm, SERVO_REF_PICKUP *current_servo_ref);

void SetPwmCcr(int pwm_ccr_left, int pwm_ccr_right, int pwm_ccr_middle, SERVO_REF_PICKUP *current_servo_ref);

void SetServoRefFire(float ref_left, float ref_right, SERVO_REF_FIRE *current_fire_ref);

void SetPwmCcrMiddle(int pwm_ccr_middle, SERVO_REF_PICKUP *current_pickup_ref);

void SetServoRefPush(float ref_push, SERVO_REF_FIRE *current_fire_ref);

void VelocityPlanning(float initialAngle, float maxAngularVelocity, float AngularAcceleration, float targetAngle, float currentTime, __IO float *currentAngle);

void SetServoRefPickupTrajectory(float ref_pitch, float ref_yaw, float ref_arm, SERVO_REF_PICKUP *current_pickup_ref);

void SetPwmCcrMiddleTrajectory(int pwm_ccr_middle, SERVO_REF_PICKUP *current_pickup_ref);

extern UPPER_STATE Upper_state;
extern SERVO_REF_PICKUP Pickup_ref;
extern SERVO_REF_FIRE Fire_ref;
extern Button button;
extern TaskHandle_t g_stateManagementTaskHandle;

#endif