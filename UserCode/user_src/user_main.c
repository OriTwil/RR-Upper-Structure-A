/*
 * @Author: szf
 * @Description: 通信线程
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
    PWMInit();

    // 开启线程
    //  CommunicateTaskStart(&ControllerData);// 通信线程(暂时不需要)
    ServoTaskStart(&ControllerData);           // 伺服线程
    StateMachineTaskStart(&ControllerData);    // 状态机线程
    StateManagemantTaskStart(&ControllerData); // 状态切换线程

    // PWMTaskStart(&ControllerData); // 仅用于测试舵机
    // FireTasksStart(&ControllerData); // 仅用于测试射环
    for (;;) {
        osDelay(1);
    }
}

// 电机初始化
void MotorInit()
{
    CANFilterInit(&hcan1);
    hDJI[Motor_id_Fire_Left].motorType  = M3508; // 射环左
    hDJI[Motor_id_Fire_Right].motorType = M3508; // 射环右
    hDJI[Motor_id_Push].motorType       = M2006; // 推环
    hDJI[Motor_id_Pitch].motorType      = M3508; // Pitch
    hDJI[Motor_id_Arm].motorType        = M3508; // Arm
    hDJI[Motor_id_Yaw].motorType        = M3508; // Yaw

    DJI_Init(); // 大疆电机初始化
}

// 舵机PWM初始化
void PWMInit()
{
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
}

// 通信初始化
void CommunicateInit(UART_HandleTypeDef *huart, mavlink_channel_t chan)
{
    // WTR_MAVLink_Init(huart, chan);
    wtrMavlink_BindChannel(huart, MAVLINK_COMM_1); // MAVLINK初始化
    CtrlDataSendChan = chan;
}