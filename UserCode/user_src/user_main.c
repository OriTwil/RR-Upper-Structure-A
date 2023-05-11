/**
 * @Author: szf
 * @Date: 2023-02-22 10:59:01
 * @LastEditTime: 2023-02-22 19:27:40
 * @LastEditors: szf
 * @Description: ER
 * @FilePath: \ER\Usercode\user_src\usermain.c
 * @WeChat:szf13373959031
 **/

#include "user_main.h"

mavlink_controller_t ControllerData = {0};
mavlink_channel_t CtrlDataSendChan = 0;

/**
 * @description: 创建线程
 * @author: szf
 * @date:
 * @return {void}
 */
void StartDefaultTask(void const *argument)
{
    //初始化
    wtrMavlink_BindChannel(&huart1, MAVLINK_COMM_0);// MAVLINK初始化
    CommunicateInit(&huart1, MAVLINK_COMM_1); // 遥控器初始化
    HAL_UART_Receive_DMA(&huart1, JoyStickReceiveData, 18); // DMA接收AS69
    MotorInit(); // DJI电机初始化
    PWMInit();

    //开启线程
	// CommunicateTaskStart(&ControllerData);// 遥控器线程
    // ServoTaskStart(&ControllerData);
    // PickUpTaskStart(&ControllerData);// 取环线程
    // FireTasksStart(&ControllerData); // 射环
    // StateManagemanttaskStart(&ControllerData);
    // PWMTaskStart(&ControllerData);
  
    for (;;) {
        osDelay(1);
    }
}

void MotorInit()
{
    CANFilterInit(&hcan1);
    hDJI[0].motorType = M3508; // 射环左
    hDJI[1].motorType = M3508; // 射环右
    hDJI[4].motorType = M3508; // Pitch
    hDJI[5].motorType = M3508; // Arm
    hDJI[6].motorType = M2006; // 推环
    
    DJI_Init(); // 大疆电机初始化
}

void PWMInit()
{
    HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
}

void CommunicateInit(UART_HandleTypeDef *huart, mavlink_channel_t chan)
{
	// WTR_MAVLink_Init(huart, chan);
	wtrMavlink_BindChannel(huart, MAVLINK_COMM_1);// MAVLINK初始化
	CtrlDataSendChan = chan;
}