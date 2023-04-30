/*** 
 * @Author: szf
 * @Date: 2023-03-11 12:51:24
 * @LastEditTime: 2023-04-30 11:15:54
 * @LastEditors: szf
 * @Description: 
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\servo.h
 * @@WeChat:szf13373959031
 */
#ifndef SERVO_H
#define SERVO_H

#include "pick_up.h"
#include "Caculate.h"
#include "usermain.h"
#include "math.h"
#include "Caculate.h"
#include "wtr_can.h"
#include "DJI.h"

#define M_PI 3.1415926

void ServoTask(void const *argument);
void ServoTaskStart(mavlink_controller_t *controldata);
#endif