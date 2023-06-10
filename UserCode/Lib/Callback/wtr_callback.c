/**
 * @description: 回调函数
 * @author: szf
 * @date:
 * @return {void}
 */

#include "wtr_callback.h"
#include "remote_control.h"

int counter   = 0;
float w_speed = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    // MAVLINK消息
    if (huart->Instance == USART_MAVLINK) {
        wtrMavlink_UARTRxCpltCallback(huart, MAVLINK_COMM_0); // 进入mavlink回调

    }
    // DJI遥控器
    else if (huart->Instance == USART_DJI_REMOTE_CONTROLLER) {
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
void wtrMavlink_MsgRxCpltCallback(mavlink_message_t *msg)
{

    switch (msg->msgid) {
        case MAVLINK_MSG_ID_CHASSIS_TO_UPPER:
            // id = 11 的消息对应的解码函数(mavlink_msg_xxx_decode)
            mavlink_msg_chassis_to_upper_decode(msg, &ChassisData); // 底盘主控
            break;
        case MAVLINK_MSG_ID_JOYSTICK_AIR:
            mavlink_msg_joystick_air_decode(msg, &msg_joystick_air);
            break;
        // ......
        default:
            break;
    }
}
