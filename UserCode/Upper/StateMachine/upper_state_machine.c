/*
 * @Author: szf
 * @Date: 2023-03-08 19:12:32
 * @LastEditTime: 2023-05-14 23:27:58
 * @LastEditors: szf
 * @Description:状态机线程
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_pick_up.c
 * @WeChat:szf13373959031
 */

#include "wtr_uart.h"
#include "tim.h"
#include "upper_state_machine.h"

// 上层机构整体状态
UPPER_STATE Upper_state =
    {
        .Pickup_state = Ready,
        .Pickup_step  = Overturn,
        .Pickup_ring  = First_Ring,
        .Fire_number  = First_Target,
};

int Fire_point = 1; // todo 遥控器改

void StateMachineTask(void const *argument)
{
    osDelay(20);
    for (;;) {
        switch (Upper_state.Pickup_state) {
            case Ready:
                // 锁死在初始状态
                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                SetServoRefFire(Fire_Ready, -Fire_Ready, &Fire_ref);
                SetPwmCcr(CCR_Left_Ready, CCR_Right_Ready, CCR_Middle_Ready, &Pickup_ref);
                SetServoRefPickupTrajectory(Ready_Pitch, Ready_Yaw, Ready_Arm, &Pickup_ref);
                break;
            case Hug:
                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                SetServoRefFire(Fire_Ready, -Fire_Ready, &Fire_ref);
                SetAllPickupTrajectory(Hug_Pitch, Hug_Yaw, Hug_Arm, Hug_CCR_Left, Hug_CCR_Right, Hug_CCR_Middle, &Pickup_ref);
                break;
            case HugBack:
                SetAllHugBackTrajectory(Ready_Pitch, Ready_Yaw, Ready_Arm, CCR_Left_Ready, CCR_Right_Ready, CCR_Middle_Ready, &Pickup_ref);
                PickupSwitchState(Ready,&Upper_state);
                break;
            case Pickup:
                // 开始取环
                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                switch (Upper_state.Pickup_step) {
                    case Overturn: // 翻转机械臂

                        switch (Upper_state.Pickup_ring) {
                            case First_Ring: // 最上层环
                                // SetPwmCcr(CCR_Left_Pickup_1, CCR_Right_Pickup_1, CCR_Middle_Opened, &Pickup_ref);
                                // SetAllPickupTrajectory(Overturn_Pitch_1,Pickup_Yaw,Overture_Arm_1,)
                                SetAllPickupTrajectory(Overturn_Pitch_1, Pickup_Yaw, Overture_Arm_1, CCR_Left_Pickup_1, CCR_Right_Pickup_1, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(2);
                                PickupSwitchStep(Clamp, &Upper_state);

                                break;
                            case Second_Ring: // 第二层环

                                SetAllPickupTrajectory(Overturn_Pitch_2, Pickup_Yaw, Overture_Arm_2, CCR_Left_Pickup_2, CCR_Right_Pickup_2, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(2);
                                PickupSwitchStep(Clamp, &Upper_state);

                                break;
                            case Third_Ring: // 第三层环
                                SetAllPickupTrajectory(Overturn_Pitch_3, Pickup_Yaw, Overture_Arm_3, CCR_Left_Pickup_3, CCR_Right_Pickup_3, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(2);
                                PickupSwitchStep(Clamp, &Upper_state);

                                break;
                            case Fourth_Ring: // 第四层环
                                // SetServoRefPickupTrajectory(60, Pickup_Yaw, -150, &Pickup_ref);
                                // SetPwmCcr(CCR_Left_Pickup_4, CCR_Right_Pickup_4, CCR_Middle_Opened, &Pickup_ref);
                                // SetServoRefPickupTrajectory(Overturn_Pitch_4, Pickup_Yaw, Overture_Arm_4, &Pickup_ref);
                                SetAllPickupTrajectory(Overturn_Pitch_4, Pickup_Yaw, Overture_Arm_4, CCR_Left_Pickup_4, CCR_Right_Pickup_4, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(2);
                                PickupSwitchStep(Clamp, &Upper_state);

                                break;
                            case Fifth_Ring:
                                // SetServoRefPickupTrajectory(60, Pickup_Yaw, -150, &Pickup_ref);
                                // SetPwmCcr(CCR_Left_Pickup_5, CCR_Right_Pickup_5, CCR_Middle_Opened, &Pickup_ref);
                                // SetServoRefPickupTrajectory(Overturn_Pitch_5, Pickup_Yaw, Overture_Arm_5, &Pickup_ref);
                                SetAllPickupTrajectory(Overturn_Pitch_5, Pickup_Yaw, Overture_Arm_5, CCR_Left_Pickup_5, CCR_Right_Pickup_5, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(2);
                                PickupSwitchStep(Clamp, &Upper_state);
                                break;
                            case Sixth_Ring:
                                // SetServoRefPickupTrajectory(60, Pickup_Yaw, -150, &Pickup_ref);
                                // SetPwmCcr(CCR_Left_Pickup_6, CCR_Right_Pickup_6, CCR_Middle_Opened, &Pickup_ref);
                                // SetServoRefPickupTrajectory(Overturn_Pitch_6, Pickup_Yaw, Overture_Arm_6, &Pickup_ref);
                                SetAllPickupTrajectory(Overturn_Pitch_6, Pickup_Yaw, Overture_Arm_6, CCR_Left_Pickup_6, CCR_Right_Pickup_6, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(2);
                                PickupSwitchStep(Clamp, &Upper_state);
                                break;
                            case Seventh_Ring:
                                // SetServoRefPickupTrajectory(60, Pickup_Yaw, -150, &Pickup_ref);
                                // SetPwmCcr(CCR_Left_Pickup_7, CCR_Right_Pickup_7, CCR_Middle_Opened, &Pickup_ref);
                                // SetServoRefPickupTrajectory(Overturn_Pitch_7, Pickup_Yaw, Overture_Arm_7, &Pickup_ref);
                                SetAllPickupTrajectory(Overturn_Pitch_7, Pickup_Yaw, Overture_Arm_7, CCR_Left_Pickup_7, CCR_Right_Pickup_7, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(2);
                                PickupSwitchStep(Clamp, &Upper_state);
                                break;
                            case Eighth_Ring:
                                // SetServoRefPickupTrajectory(60, Pickup_Yaw, -150, &Pickup_ref);
                                // SetPwmCcr(CCR_Left_Pickup_8, CCR_Right_Pickup_8, CCR_Middle_Opened, &Pickup_ref);
                                // SetServoRefPickupTrajectory(Overturn_Pitch_8, Pickup_Yaw, Overture_Arm_8, &Pickup_ref);
                                SetAllPickupTrajectory(Overturn_Pitch_8, Pickup_Yaw, Overture_Arm_8, CCR_Left_Pickup_8, CCR_Right_Pickup_8, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(2);
                                PickupSwitchStep(Clamp, &Upper_state);
                                break;
                            case Ninth_Ring:
                                // SetServoRefPickupTrajectory(60, Pickup_Yaw, -150, &Pickup_ref);
                                // SetPwmCcr(CCR_Left_Pickup_9, CCR_Right_Pickup_9, CCR_Middle_Opened, &Pickup_ref);
                                // SetServoRefPickupTrajectory(Overturn_Pitch_9, Pickup_Yaw, Overture_Arm_9, &Pickup_ref);
                                SetAllPickupTrajectory(Overturn_Pitch_9, Pickup_Yaw, Overture_Arm_9, CCR_Left_Pickup_9, CCR_Right_Pickup_9, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(2);
                                PickupSwitchStep(Clamp, &Upper_state);
                                break;
                            case Tenth_Ring: // 第四层环
                                // SetServoRefPickupTrajectory(60, Pickup_Yaw, -150, &Pickup_ref);
                                // SetPwmCcr(CCR_Left_Pickup_10, CCR_Right_Pickup_10, CCR_Middle_Opened, &Pickup_ref);
                                // SetServoRefPickupTrajectory(Overturn_Pitch_10, Pickup_Yaw, Overture_Arm_10, &Pickup_ref);
                                SetAllPickupTrajectory(Overturn_Pitch_10, Pickup_Yaw, Overture_Arm_10, CCR_Left_Pickup_10, CCR_Right_Pickup_10, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(2);
                                PickupSwitchStep(Clamp, &Upper_state);

                                break;
                            default:
                                // 错误处理还没想好
                                break;
                        }
                        break;
                    case Clamp: // 收紧爪子
                        SetPwmCcrMiddle(CCR_Middle_Closed, &Pickup_ref);
                        vTaskDelay(500);
                        PickupSwitchStep(Overturn_back, &Upper_state);
                        break;
                    case Overturn_back: // 机械臂收回
                        // SetServoRefPickupTrajectory(Overture_Pitch_back, 360, -150, &Pickup_ref);
                        // SetPwmCcr(CCR_Left_Ready, CCR_Right_Ready, CCR_Middle_Closed, &Pickup_ref);
                        SetAllPickupTrajectory(Overture_Pitch_back, Overturn_Yaw_Transition, Overturn_Arm_back, CCR_Left_Ready, CCR_Right_Ready, CCR_Middle_Closed, &Pickup_ref);
                        // SetServoRefPickupTrajectory(Overture_Pitch_back, Overturn_Yaw_Transition, Overturn_Arm_back, &Pickup_ref);
                        PickupSwitchStep(Release, &Upper_state);
                        vTaskDelay(20);
                        break;
                    case Release: // 松开爪子，自动切换到射环
                        SetPwmCcrMiddle(Fire_CCR_Middle, &Pickup_ref);
                        vTaskDelay(100);
                        PickupSwitchStep(Overturn, &Upper_state);
                        PickupSwitchState(Fire, &Upper_state);
                        break;
                    default:
                        // 错误处理还没想好
                        break;
                }
                break;
            case Fire:
                // 射环
                SetServoRefFire(Fire_Ready, -Fire_Ready, &Fire_ref);
                switch (Fire_point) // 点位号(预先将点位编号)
                {
                    case 1:                              // todo 确定战术
                        switch (Upper_state.Fire_number) // 几号柱子(预先将柱子编号)
                        {
                            case First_Target:
                                SetAllPickupTrajectory(Fire_Pitch_1_1, Fire_Yaw_1_1, Fire_Arm, Fire_CCR_Left, Fire_CCR_Right, Fire_CCR_Middle, &Pickup_ref);
                                SetServoRefFire(-Fire_1_1, Fire_1_1, &Fire_ref);
                                vTaskDelay(1500);
                                SetServoRefPush(Fire_Push_Extend, &Fire_ref);
                                vTaskDelay(2000);
                                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                                SetPwmCcr(CCR_Left_Ready, CCR_Right_Ready, CCR_Middle_Ready, &Pickup_ref);
                                vTaskDelay(200);
                                PickupSwitchState(Ready, &Upper_state);
                                break;
                            case Second_Target:
                                SetServoRefPickupTrajectory(Fire_Pitch_1_2, Fire_Yaw_1_2, Fire_Arm, &Pickup_ref);
                                SetServoRefFire(-Fire_1_2, Fire_1_2, &Fire_ref);
                                vTaskDelay(300);
                                SetServoRefPush(Fire_Push_Extend, &Fire_ref);
                                vTaskDelay(500);
                                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                                vTaskDelay(50);
                                PickupSwitchState(Ready, &Upper_state);
                                break;
                            default:
                                break;
                        }
                        break;
                    case 2:
                        switch (Upper_state.Fire_number) {
                            case Third_Target:
                                SetServoRefPickupTrajectory(Fire_Pitch_2_3, Fire_Yaw_2_3, Fire_Arm, &Pickup_ref);
                                SetServoRefFire(-Fire_Pitch_2_3, Fire_Pitch_2_3, &Fire_ref);
                                vTaskDelay(300);
                                SetServoRefPush(Fire_Push_Extend, &Fire_ref);
                                vTaskDelay(500);
                                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                                vTaskDelay(50);
                                PickupSwitchState(Ready, &Upper_state);
                                break;
                            case Fourth_Target:
                                SetServoRefPickupTrajectory(Fire_Pitch_2_4, Fire_Yaw_2_4, Fire_Arm, &Pickup_ref);
                                SetServoRefFire(-Fire_Pitch_2_4, Fire_Pitch_2_4, &Fire_ref);
                                vTaskDelay(300);
                                SetServoRefPush(Fire_Push_Extend, &Fire_ref);
                                vTaskDelay(500);
                                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                                vTaskDelay(50);
                                PickupSwitchState(Ready, &Upper_state);
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        vTaskDelay(1);
    }
}

void StateMachineTestTask(void const *argument)
{
    osDelay(2);
    for (;;) {
        vTaskDelay(2);
    }
}

void StateMachineTaskStart()
{
    osThreadDef(StateMachine, StateMachineTask, osPriorityNormal, 0, 512);
    osThreadCreate(osThread(StateMachine), NULL);

    // osThreadDef(upper_rr_test, StateMachineTestTask, osPriorityBelowNormal, 0, 512);
    // osThreadCreate(osThread(upper_rr_test), NULL);
}

/**
 * @brief 切换取环状态(	Ready,Pickup,Fire )
 *
 * @param (PICKUP_STATE) target_pick_up_state
 * @param (UPPER_STATE *) current_upper_state
 * @return
 */
void PickupSwitchState(PICKUP_STATE target_pick_up_state, UPPER_STATE *current_upper_state)
{
    xSemaphoreTakeRecursive(current_upper_state->xMutex_upper, (TickType_t)10);
    current_upper_state->Pickup_state = target_pick_up_state;
    xSemaphoreGiveRecursive(current_upper_state->xMutex_upper);
}

/**
 * @brief 切换取环所在步骤(	Overturn,Clamp,Overturn_back,Release )
 *
 */
void PickupSwitchStep(PICKUP_STEP target_pick_up_step, UPPER_STATE *current_upper_state)
{
    xSemaphoreTakeRecursive(current_upper_state->xMutex_upper, (TickType_t)10);
    current_upper_state->Pickup_step = target_pick_up_step;
    xSemaphoreGiveRecursive(current_upper_state->xMutex_upper);
}

/**
 * @brief 切换取环目标(1 2 3 4 5)
 *
 */
void PickupSwitchRing(PICKUP_RING target_pick_up_Ring, UPPER_STATE *current_upper_state)
{
    xSemaphoreTakeRecursive(current_upper_state->xMutex_upper, (TickType_t)10);
    current_upper_state->Pickup_ring = target_pick_up_Ring;
    xSemaphoreGiveRecursive(current_upper_state->xMutex_upper);
}

/**
 * @brief 切换射环的目标
 *
 */
void FireSwitchNumber(FIRE_NUMBER target_fire_number, UPPER_STATE *current_upper_state)
{
    xSemaphoreTakeRecursive(current_upper_state->xMutex_upper, (TickType_t)10);
    current_upper_state->Fire_number = target_fire_number;
    xSemaphoreGiveRecursive(current_upper_state->xMutex_upper);
}
