#ifndef PICK_UP_H
#define PICK_UP_H

#include "user_main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include <math.h>

#define Ongoing 1
#define Finished 0
#define Overturn_Pitch 156
#define Overture_Arm -210 
#define Overture_Pitch_back 90
#define Overturn_Arm_back 0
#define Fire_Arm -30
#define Fire_Angle 73

void rrPickUpTask(void const *argument);
void rrPickUpTestTask(void const *argument);
void DeadBand(double x, double y, double *new_x, double *new_y, double threshould);
void PickUpTaskStart(mavlink_controller_t *controldata);

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
}PICKUP_NUMBER;

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
    uint32_t last_tick;
    uint32_t button_min_time;
}Button;

extern PICKUP_STATE Pickup_state;
extern PICKUP_STEP Pickup_step;
extern PICKUP_NUMBER pickup_number;
extern FIRE_NUMBER fire_number;
extern Button button;

#endif
