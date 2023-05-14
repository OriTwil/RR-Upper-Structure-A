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

void StateMachineTaskStart(mavlink_controller_t *controldata);

#endif
