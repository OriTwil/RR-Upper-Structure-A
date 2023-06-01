/*** 
 * @Author: szf
 * @Date: 2023-04-28 22:41:21
 * @LastEditTime: 2023-05-11 15:48:45
 * @LastEditors: szf
 * @Description: 弃用，并入Servo线程，现在用于测试舵机
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\upper_pwm_out.h
 * @@WeChat:szf13373959031
 */
#ifndef PWM_OUT_H
#define PWM_OUT_H

#include "upper_start.h"
#include "tim.h"

void PWMTask(void const *argument);
void PWMTestTask(void const *argument);
void PWMTaskStart();

#endif
