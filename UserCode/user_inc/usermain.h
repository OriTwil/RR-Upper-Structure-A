/*** 
 * @Author: szf
 * @Date: 2023-02-22 11:56:47
 * @LastEditTime: 2023-04-30 11:11:27
 * @LastEditors: szf
 * @Description: 
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\usermain.h
 * @@WeChat:szf13373959031
 */


#ifndef USERMAIN_H
#define USERMAIN_H

#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include "Caculate.h"
#include "wtr_can.h"
#include "DJI.h"
#include <math.h>
#include "main.h"
#include "wtr_mavlink.h"
#include "ctrl_data_sender.h"
#include "beep.h"
#include "servo.h"
#include "pick_up.h"
#include "wtr_uart.h"
#include "usercallback.h"
#include "pwm_out.h"
#include "fire.h"
#include "pick_up.h"

extern mavlink_controller_t ControllerData;

void MotorInit();
void PWMInit();

#endif