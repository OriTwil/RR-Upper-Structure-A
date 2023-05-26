/*
 * @Author: szf
 * @Description: 主函数(初始化与创建线程)
 *
 */
#include "user_main.h"

volatile mavlink_controller_t ControllerData    = {0};
volatile mavlink_chassis_to_upper_t ChassisData = {0};
volatile mavlink_channel_t CtrlDataSendChan     = MAVLINK_COMM_0;

/**
 * @description: 创建线程
 * @author: szf
 * @date:
 * @return {void}
 */
void StartDefaultTask(void const *argument)
{
    // 初始化
    CommunicateInit(); // 遥控器初始化
    MotorInit();       // DJI电机初始化
    PWMInit();         // 舵机初始化
    UpperStateInit();  // 状态机初始化

    // 开启线程
    CommunicateTaskStart();                 // 通信线程
    ServoTaskStart();                       // 伺服线程
    StateMachineTaskStart(&ControllerData); // 状态机线程
    StateManagemantTaskStart();             // 状态切换线程

    // PWMTaskStart(&ControllerData); // 仅用于测试舵机
    // FireTasksStart(&ControllerData); // 仅用于测试射环
    for (;;) {
        vTaskDelay(5);
    }
}
