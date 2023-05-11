#ifndef _CACULATE_H__
#define _CACULATE_H__

#include "user_main.h"
#include "wtr_dji.h"

void positionServo(float ref, DJI_t *motor);

void speedServo(float ref, DJI_t *motor);

#endif