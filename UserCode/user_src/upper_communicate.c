/*
 * @Author: szf
 * @Date: 2023-02-23 20:07:26
 * @LastEditTime: 2023-05-13 13:45:09
 * @LastEditors: szf
 * @Description: 通信线程
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_communicate.c
 * @WeChat:szf13373959031
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
