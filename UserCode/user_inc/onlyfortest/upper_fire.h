/*** 
 * @Author: szf
 * @Date: 2023-04-28 23:38:51
 * @LastEditTime: 2023-05-11 15:14:05
 * @LastEditors: szf
 * @Description: 弃用，并入servo,现在用于测试射环
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\fire.h
 * @@WeChat:szf13373959031
 */

#ifndef FIRE_H
#define FIRE_H

#include "user_main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include <math.h>

void FireTask(void const *argument);
void FireTestTask(void const *argument);
void FireTaskStart(mavlink_controller_t *controldata);
#endif
