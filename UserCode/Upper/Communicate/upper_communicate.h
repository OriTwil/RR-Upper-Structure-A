/**
 * @file controller_data_sender.h
 * @author TITH (1023515576@qq.com)
 * @brief 发送遥控器原始数据
 * @version 0.1
 * @date 2022-07-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "upper_start.h"
#include "upper_commen.h"

// 按键通知值定义
#define BUTTON1_NOTIFICATION (1 << 0)
#define BUTTON2_NOTIFICATION (1 << 1)
#define BUTTON3_NOTIFICATION (1 << 2)

void CommunicateTaskStart();
void CommunicateInit();

extern mavlink_controller_t ControllerData;
extern mavlink_channel_t CtrlDataSendChan;
extern mavlink_chassis_to_upper_t ChassisData;
