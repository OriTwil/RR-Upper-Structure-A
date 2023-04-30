/*** 
 * @Author: szf
 * @Date: 2023-04-28 23:38:51
 * @LastEditTime: 2023-04-30 16:16:54
 * @LastEditors: szf
 * @Description: 
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\fire.h
 * @@WeChat:szf13373959031
 */
#ifndef FIRE_H
#define FIRE_H

#include "usermain.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include "Caculate.h"
#include "wtr_can.h"
#include "DJI.h"
#include <math.h>
#include "ctrl_data_sender.h"
#include "beep.h"
#include "pick_up.h"

void FireTask(void const *argument);
void FireTestTask(void const *argument);
void FireTaskStart(mavlink_controller_t *controldata);
#endif
