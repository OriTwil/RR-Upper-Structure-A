/*** 
 * @Author: szf
 * @Date: 2023-03-11 12:51:24
 * @LastEditTime: 2023-05-11 16:02:24
 * @LastEditors: szf
 * @Description: 
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\upper_servo.h
 * @@WeChat:szf13373959031
 */
#ifndef SERVO_H
#define SERVO_H

#include "upper_pick_up.h"
#include "user_main.h"
#include "math.h"
#include "upper_state_management.h"

#define M_PI 3.1415926

void ServoTask(void const *argument);
void ServoTaskStart(mavlink_controller_t *controldata);
#endif