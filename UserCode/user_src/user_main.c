/*
 * @Author: szf
 * @Description: 主函数(初始化与创建线程)
 *
 */
#include "user_main.h"

mavlink_controller_t ControllerData    = {0};
mavlink_chassis_to_upper_t ChassisData = {0};
mavlink_channel_t CtrlDataSendChan     = MAVLINK_COMM_0;

/**
 * @description: 创建线程
 * @author: szf
 * @date:
 * @return {void}
 */
void StartDefaultTask(void const *argument)
{
    // 初始化
    wtrMavlink_BindChannel(&huart1, MAVLINK_COMM_0);        // MAVLINK初始化
    CommunicateInit(&huart1, MAVLINK_COMM_1);               // 遥控器初始化
    HAL_UART_Receive_DMA(&huart1, JoyStickReceiveData, 18); // DMA接收AS69
    MotorInit();                                            // DJI电机初始化
    PWMInit();                                              // 舵机初始化
    UpperStateInit();                                       // 状态机初始化

    // 开启线程
    // CommunicateTaskStart(&ControllerData);     // 通信线程
    ServoTaskStart(&ControllerData);           // 伺服线程
    // StateMachineTaskStart(&ControllerData);    // 状态机线程
    StateManagemantTaskStart(&ControllerData); // 状态切换线程

    // PWMTaskStart(&ControllerData); // 仅用于测试舵机
    // FireTasksStart(&ControllerData); // 仅用于测试射环
    for (;;) {
        osDelay(1);
    }
}
