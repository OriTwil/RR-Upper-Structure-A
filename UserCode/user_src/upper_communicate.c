/*
 * @Author: szf
 * @Date: 2023-02-23 20:07:26
 * @LastEditTime: 2023-05-11 16:26:42
 * @LastEditors: szf
 * @Description: 
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_communicate.c
 * @WeChat:szf13373959031
 */
/**
 * @file controller_data_sender.c
 * @author TITH (1023515576@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "upper_communicate.h"

void CommunicateTask(void const *argument)
{
	while (1)
	{
		mavlink_msg_controller_send_struct(CtrlDataSendChan, argument);
		osDelay(10);
	}
}

void CommunicateTaskStart(mavlink_controller_t* controller)
{
	osThreadDef(communicate, CommunicateTask, osPriorityNormal, 0, 512);
	osThreadCreate(osThread(communicate), controller);
}
