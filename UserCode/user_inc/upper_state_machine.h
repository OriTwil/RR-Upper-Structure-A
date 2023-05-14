#ifndef PICK_UP_H
#define PICK_UP_H

#include "user_main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include <math.h>
#include "upper_state_management.h"

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
void PickUpTaskStart(mavlink_controller_t *controldata);

#endif
