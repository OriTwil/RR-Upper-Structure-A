/*
 * @Author: szf
 * @Date: 2023-03-30 16:29:58
 * @LastEditTime: 2023-04-28 21:35:17
 * @LastEditors: szf
 * @Description: 
 * @FilePath: \RR-Upper-Structure\UserCode\user_src\usercallback.c
 * @WeChat:szf13373959031
 */
/**
 * @description: 回调函数
 * @param {UART_HandleTypeDef} *huart
 * @author: szf
 * @date:
 * @return {void}
 */

#include "usermain.h"
#include "usercallback.h"
#include "wtr_uart.h"
#include "uart_device.h"
#include "wtr_mavlink.h"

int counter          = 0;
int test             = 0;
float w_speed        = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    test++;
    // MAVLINK消息
    if (huart->Instance == USART2) {
        wtrMavlink_UARTRxCpltCallback(huart, MAVLINK_COMM_0); // 进入mavlink回调
    }
    // DJI遥控器
    else if (huart->Instance == USART1)
    {
        AS69_Decode(); // AS69解码
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	UD_TxCpltCallback(huart);
}

/**
 * @brief 接收到完整消息且校验通过后会调用这个函数。在这个函数里调用解码函数就可以向结构体写入收到的数据
 *
 * @param msg 接收到的消息
 * @return
 */
extern mavlink_controller_t ControllerData;
void wtrMavlink_MsgRxCpltCallback(mavlink_message_t *msg)
{

    switch (msg->msgid) {
        case 9:
            // id = 9 的消息对应的解码函数(mavlink_msg_xxx_decode)
            break;
        case 1:
            // id = 1 的消息对应的解码函数(mavlink_msg_xxx_decode)
            mavlink_msg_controller_decode(msg, &ControllerData); // 遥控器 
            break;
        // ......
        default:
            break;
    }
}
