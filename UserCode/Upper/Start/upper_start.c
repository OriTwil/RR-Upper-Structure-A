/*
 * @Author: szf
 * @Description: 主函数(初始化与创建线程)
 *
 */
#include "upper_start.h"
#include "upper_commen.h"
#include "upper_operate_app.h"

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
    // CommunicateTaskStart();                 // 通信线程
    // ServoTaskStart();                       // 伺服线程
    StateMachineTaskStart(); // 状态机线程
    StateManagemantTaskStart();             // 状态切换线程

    // PWMTaskStart(); // 仅用于测试舵机
    // FireTasksStart(&ControllerData); // 仅用于测试射环
    for (;;) {
        vTaskDelay(5);
    }
}
