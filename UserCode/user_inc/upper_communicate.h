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

#include "wtr_mavlink.h"
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "user_main.h"
#include "upper_state_management.h"

// 按键通知值定义
#define BUTTON1_NOTIFICATION (1 << 0)
#define BUTTON2_NOTIFICATION (1 << 1)
#define BUTTON3_NOTIFICATION (1 << 2)

void CommunicateTaskStart(mavlink_controller_t* controller);
void CommunicateInit(UART_HandleTypeDef *huart, mavlink_channel_t chan);
