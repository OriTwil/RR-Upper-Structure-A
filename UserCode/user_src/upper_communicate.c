/*
 * @Author: szf
 * @Version: 
 * @Date: 2023-05-13 23:29:42
 * @LastEditTime: 2023-05-14 22:50:24
 * @LastEditors: szf
 * @Description: 与Chassis主控通信
 * @WeChat:szf13373959031
 */

#include "upper_communicate.h"

/**
 * @description: 通信线程
 * @param {  } while
 * @param {  } osDelay
 * @author: szf
 * @return {void}
 */
void CommunicateTask(void const *argument)
{
    while (1) {
        mavlink_msg_controller_send_struct(CtrlDataSendChan, argument);
        osDelay(10);
    }
}

/**
 * @description: 创建通信线程
 * @param {mavlink_controller_t} *controller
 * @author: szf
 * @return {void}
 */
void CommunicateTaskStart(mavlink_controller_t *controller)
{
    osThreadDef(communicate, CommunicateTask, osPriorityNormal, 0, 512);
    osThreadCreate(osThread(communicate), controller);
}
