/*** 
 * @Author: szf
 * @Date: 2023-02-22 11:56:47
 * @LastEditTime: 2023-05-11 16:26:23
 * @LastEditors: szf
 * @Description: 
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\user_main.h
 * @@WeChat:szf13373959031
 */


#ifndef USERMAIN_H
#define USERMAIN_H
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include <math.h>

#include "wtr_mavlink.h"
#include "wtr_uart.h"
#include "wtr_can.h"
#include "wtr_dji.h"
#include "uart_device.h"

#include "user_callback.h"
#include "user_beep.h"
#include "user_caculate.h"

#include "upper_fire.h"
#include "user_time.h"
#include "user_config.h"
#include "upper_pwm_out.h"
#include "upper_servo.h"
#include "upper_pick_up.h"
#include "upper_communicate.h"

extern mavlink_controller_t ControllerData;
extern mavlink_channel_t CtrlDataSendChan;

void MotorInit();
void PWMInit();
void CommunicateInit(UART_HandleTypeDef *huart, mavlink_channel_t chan);

#endif