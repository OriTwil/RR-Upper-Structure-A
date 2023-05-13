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
    Upper_state.xMutex_upper = xSemaphoreCreateMutex(); 
    Servo_ref.xMutex_servo = xSemaphoreCreateMutex();

    osThreadDef(statemanagement, StateManagemantTask, osPriorityNormal, 0, 512);
    osThreadCreate(osThread(statemanagement), NULL);

    // osThreadDef(statemanagementtest,StateManagemantTestTask,osPriorityBelowNormal,0,512);
    // osThreadCreate(osThread(statemanagementtest),NULL);
}

void PickupSwitchState(PICKUP_STATE target_pick_up_state,UPPER_STATE *current_upper_state)
{
    xSemaphoreTake( current_upper_state->xMutex_upper, ( TickType_t ) 10 );
    current_upper_state->Pickup_state = target_pick_up_state;
    xSemaphoreGive( current_upper_state->xMutex_upper );
}

void PickupSwitchStep(PICKUP_STEP target_pick_up_step,UPPER_STATE *current_upper_state)
{
    xSemaphoreTake( current_upper_state->xMutex_upper, ( TickType_t ) 10 );
    current_upper_state->Pickup_step = target_pick_up_step;
    xSemaphoreGive( current_upper_state->xMutex_upper );
}

void PickupSwitchPoint(PICKUP_POINT target_pick_up_point,UPPER_STATE *current_upper_state)
{
    xSemaphoreTake( current_upper_state->xMutex_upper, ( TickType_t ) 10 );
    current_upper_state->Pickup_point = target_pick_up_point;
    xSemaphoreGive( current_upper_state->xMutex_upper );
}

void FireSwitchNumber(FIRE_NUMBER target_fire_number,UPPER_STATE *current_upper_state)
{
    xSemaphoreTake( current_upper_state->xMutex_upper, ( TickType_t ) 10 );
    current_upper_state->Fire_number = target_fire_number;
    xSemaphoreGive( current_upper_state->xMutex_upper );
}

void SetServoRef(float ref_pitch,float ref_yaw,float ref_arm,SERVO_REF_PICKUP *current_servo_ref)
{
    xSemaphoreTake( current_servo_ref->xMutex_servo, ( TickType_t ) 10 );
    current_servo_ref->position_servo_ref_pitch = ref_pitch;
    current_servo_ref->position_servo_ref_yaw = ref_yaw;
    current_servo_ref->position_servo_ref_arm = ref_arm;
    xSemaphoreGive( current_servo_ref->xMutex_servo );
}

void SetPwmCcr(int pwm_ccr_left,int pwm_ccr_right,int pwm_ccr_middle,SERVO_REF_PICKUP *current_servo_ref)
{
    xSemaphoreTake( current_servo_ref->xMutex_servo, ( TickType_t ) 10 );
    current_servo_ref->pwm_ccr_left = pwm_ccr_left;
    current_servo_ref->pwm_ccr_right = pwm_ccr_left;
    current_servo_ref->pwm_ccr_middle = pwm_ccr_left;
    xSemaphoreGive( current_servo_ref->xMutex_servo );
}