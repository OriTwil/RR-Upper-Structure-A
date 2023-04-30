#ifndef PICK_UP_H
#define PICK_UP_H

#include "usermain.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include "Caculate.h"
#include "wtr_can.h"
#include "DJI.h"
#include <math.h>
#include "ctrl_data_sender.h"
#include "beep.h"
#include "servo.h"

#define Ongoing 1
#define Finished 0
#define Overturn_Pitch 156
#define Overture_Arm -210 
#define Overture_Pitch_back 90
#define Overturn_Arm_back 0
#define Fire_Arm -30
#define Fire_Angle 65

void rrPickUpTask(void const *argument);
void rrPickUpTestTask(void const *argument);
void DeadBand(double x, double y, double *new_x, double *new_y, double threshould);
void PickUpTaskStart(mavlink_controller_t *controldata);
// 状态
typedef enum
{
	Motionless,
	Overturn,
	Clamp,
	Pitch_Overturn_back,
	Arm_Overturn_back,
	Release,
	Fire
}Mode;

typedef struct
{
    uint32_t last_tick;
    uint32_t button_min_time;
}Button;

extern bool Pickup_state;
extern Mode Pickup_mode;
extern Button button;
#endif
