/*** 
 * @Author: szf
 * @Date: 2023-03-11 12:51:24
 * @LastEditTime: 2023-05-11 16:02:24
 * @LastEditors: szf
 * @Description: 以固定频率进行伺服
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\upper_servo.h
 * @@WeChat:szf13373959031
 */
#ifndef UPPER_SERVO_H
#define UPPER_SERVO_H

#include "upper_state_machine.h"
#include "user_main.h"
#include "math.h"
#include "upper_state_management.h"
#include "user_config.h"

void ServoTaskStart(mavlink_controller_t *controldata);
void MotorInit();
void PWMInit();

#endif