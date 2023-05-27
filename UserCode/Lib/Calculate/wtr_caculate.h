#ifndef USER_CACULATE_H
#define USER_CACULATE_H

#include "upper_start.h"
#include "wtr_dji.h"

void positionServo(float ref, DJI_t *motor);

void speedServo(float ref, DJI_t *motor);

void DeadBand(double x, double y, double *new_x, double *new_y, double threshould);

#endif