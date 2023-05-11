/*
 * @Author: szf
 * @Date: 2023-05-11 16:08:17
 * @LastEditTime: 2023-05-11 16:19:38
 * @LastEditors: szf
 * @Description: 任务切换线程
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_state_management.c
 * @WeChat:szf13373959031
 */
#include "upper_state_management.h"

void StateManagemantTask(void const *argument)
{
    uint32_t PreviousWakeTime = osKernelSysTick();
    osDelay(20);
    for(;;)
    {
        osDelayUntil(&PreviousWakeTime, 5);
    }
}

void StateManagemanttaskStart(mavlink_controller_t *controldata)
{
    osThreadDef(statemanagement, StateManagemantTask, osPriorityBelowNormal, 0, 512);
    osThreadCreate(osThread(statemanagement), NULL);

    // osThreadDef(statemanagementtest,StateManagemantTestTask,osPriorityBelowNormal,0,512);
    // osThreadCreate(osThread(statemanagementtest),NULL);
}