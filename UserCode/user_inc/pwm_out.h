/*** 
 * @Author: szf
 * @Date: 2023-04-28 22:41:21
 * @LastEditTime: 2023-04-30 18:57:36
 * @LastEditors: szf
 * @Description: 
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\pwm_out.h
 * @@WeChat:szf13373959031
 */
#ifndef PWM_OUT_H
#define PWM_OUT_H

#include "pick_up.h"
#include "usermain.h"
#include "tim.h"

void PWMTask(void const *argument);
void PWMTestTask(void const *argument);
void PWMTaskStart(mavlink_controller_t *controldata);

#endif
