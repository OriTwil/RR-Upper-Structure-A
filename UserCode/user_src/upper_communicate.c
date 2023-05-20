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
#include "upper_state_management.h"

/**
 * @description: 通信线程
 * @param {  } while
 * @param {  } osDelay
 * @author: szf
 * @return {void}
 */
void CommunicateTask(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    vTaskDelay(20);
    while (1) {
        vPortEnterCritical();
        // 发送按键通知
        if (1/* 判断按键1是否按下 */) {
            xTaskNotify(g_stateManagementTaskHandle, BUTTON1_NOTIFICATION, eSetBits);
        }
        if (1/* 判断按键2是否按下 */) {
            xTaskNotify(g_stateManagementTaskHandle, BUTTON2_NOTIFICATION, eSetBits);
        }
        if (1/* 判断按键3是否按下 */) {
            xTaskNotify(g_stateManagementTaskHandle, BUTTON3_NOTIFICATION, eSetBits);
        }
        vPortExitCritical();
        mavlink_msg_controller_send_struct(CtrlDataSendChan, argument);
        // osDelay(10);
        vTaskDelayUntil(&PreviousWakeTime,3);
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
    osThreadCreate(osThread(communicate), NULL);
}

// 通信初始化
void CommunicateInit(UART_HandleTypeDef *huart, mavlink_channel_t chan)
{
    // WTR_MAVLink_Init(huart, chan);
    wtrMavlink_BindChannel(huart, MAVLINK_COMM_1); // MAVLINK初始化
    CtrlDataSendChan = chan;
}