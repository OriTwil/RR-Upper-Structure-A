#ifndef UPPER_STATE_MANAGEMENT
#define UPPER_STATE_MANAGEMENT

#include "user_main.h"

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
	First_Ring,
	Second_Ring,
	Third_Ring,
	Fourth_Ring,
	Fifth_Ring
}PICKUP_RING;

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
    PICKUP_RING Pickup_ring;
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
    SemaphoreHandle_t xMutex_servo_pickup;
}SERVO_REF_PICKUP;

typedef struct
{
    float speed_servo_ref_left;
	float speed_servo_ref_right;
	float position_servo_ref_push;
	SemaphoreHandle_t xMutex_servo_fire;
}SERVO_REF_FIRE;

typedef struct
{
    uint32_t last_tick;
    uint32_t button_min_time;
}Button;

void PickupSwitchState(PICKUP_STATE target_pick_up_state,UPPER_STATE *current_upper_state);

void PickupSwitchStep(PICKUP_STEP target_pick_up_step,UPPER_STATE *current_upper_state);

void PickupSwitchRing(PICKUP_RING target_pick_up_Ring,UPPER_STATE *current_upper_state);

void FireSwitchNumber(FIRE_NUMBER target_fire_number,UPPER_STATE *current_upper_state);

void SetServoRefPickup(float ref_pitch,float ref_yaw,float ref_arm,SERVO_REF_PICKUP *current_servo_ref);

void SetPwmCcr(int pwm_ccr_left,int pwm_ccr_right,int pwm_ccr_middle,SERVO_REF_PICKUP *current_servo_ref);

void SetServoRefFire(float ref_left,float ref_right,float ref_middle,SERVO_REF_FIRE *current_fire_ref);

extern UPPER_STATE Upper_state;
extern SERVO_REF_PICKUP Pickup_ref;
extern SERVO_REF_FIRE Fire_ref;
extern Button button;

#endif