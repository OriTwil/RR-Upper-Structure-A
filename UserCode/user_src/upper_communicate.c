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
#include "wtr_uart.h"
// #include "upper_state_management.h"

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
        vTaskDelayUntil(&PreviousWakeTime,3);
    }
}

/**
 * @description: 创建通信线程
 * @param {mavlink_controller_t} *controller
 * @author: szf
 * @return {void}
 */
void CommunicateTaskStart()
{
    osThreadDef(communicate, CommunicateTask, osPriorityNormal, 0, 512);
    osThreadCreate(osThread(communicate), NULL);
}

// 通信初始化
void CommunicateInit()
{
    wtrMavlink_BindChannel(&huart_Mavlink, MAVLINK_COMM_0); // 接收板间通信MAVLINK
    wtrMavlink_StartReceiveIT(MAVLINK_COMM_0);

    HAL_UART_Receive_DMA(&huart_AS69, JoyStickReceiveData, 18); // DMA接收AS69
}