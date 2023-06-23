#ifndef UPPER_STATE_MACHINE_H
#define UPPER_STATE_MACHINE_H

#include "upper_start.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include <math.h>
#include "upper_commen.h"

void StateMachineTaskStart();

void PickupSwitchState(PICKUP_STATE target_pick_up_state, UPPER_STATE *current_upper_state);

void PickupSwitchStep(PICKUP_STEP target_pick_up_step, UPPER_STATE *current_upper_state);

void PickupSwitchRing(PICKUP_RING target_pick_up_Ring, UPPER_STATE *current_upper_state);

void FireSwitchNumber(FIRE_NUMBER target_fire_number, UPPER_STATE *current_upper_state);

void PointSwitchNumber(CHASSIS_POINT target_point,CHASSIS_STATE *Chassis_State);

CHASSIS_POINT ReadChassisPoint(CHASSIS_STATE *Chassis_State);

PICKUP_STATE ReadUpperState(UPPER_STATE *current_upper_state);

extern UPPER_STATE Upper_state;
extern CHASSIS_STATE Chassis_state;
#endif
