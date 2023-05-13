#ifndef UPPER_STATE_MANAGEMENT
#define UPPER_STATE_MANAGEMENT

#include "user_main.h"

// 状态
typedef enum
{
	Overturn,
	Clamp,
	Pitch_Overturn_back,
	Arm_Overturn_back,
	Release,
}PICKUP_STEP;

typedef enum
{
	Ready,
	Pickup,
	Fire
}PICKUP_STATE;

typedef enum
{
	First_Point,
	Second_Point,
	Third_Point,
	Fourth_Point,
	Fifth_Point
}PICKUP_POINT;

typedef enum
{
	First_Target,
	Second_Target,
	Third_Target,
	Fourth_Target,
	Fifth_Target
}FIRE_NUMBER;

typedef struct 
{
    PICKUP_STATE Pickup_state;
    PICKUP_STEP Pickup_step;
    PICKUP_POINT Pickup_point;
    FIRE_NUMBER Fire_number;
    SemaphoreHandle_t  xMutex_upper;
}UPPER_STATE;

typedef struct
{
    float position_servo_ref_pitch;
	float position_servo_ref_yaw;
	float position_servo_ref_arm;
	int pwm_ccr_left;
	int pwm_ccr_right;
	int pwm_ccr_middle;
    SemaphoreHandle_t xMutex_servo;
}SERVO_REF_PICKUP;

typedef struct
{
    float position_servo_ref_left;
	float position_servo_ref_right;
	float position_servo_ref_push;
}SERVO_REF_FIRE;

void PickupSwitchState(PICKUP_STATE target_pick_up_state,UPPER_STATE *current_upper_state);

void PickupSwitchStep(PICKUP_STEP target_pick_up_step,UPPER_STATE *current_upper_state);

void PickupSwitchPoint(PICKUP_POINT target_pick_up_point,UPPER_STATE *current_upper_state);

void FireSwitchNumber(FIRE_NUMBER target_fire_number,UPPER_STATE *current_upper_state);

void SetServoRef(float ref_pitch,float ref_yaw,float ref_arm,SERVO_REF_PICKUP *current_servo_ref);

void SetPwmCcr(int pwm_ccr_left,int pwm_ccr_right,int pwm_ccr_middle,SERVO_REF_PICKUP *current_servo_ref);

extern UPPER_STATE Upper_state;
extern SERVO_REF Servo_ref;
extern SERVO_REF_FIRE Fire_ref;

#endif