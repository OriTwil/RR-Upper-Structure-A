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

int Fire_point_temp = 1; // 接收当前底盘所在点位

void StateMachineTask(void const *argument)
{
    osDelay(20);
    for (;;) {
        switch (Upper_state.Pickup_state) {
            case Ready:
                // 锁死在初始状态
                SetServoRefPickup(Ready_Pitch, Ready_Yaw, Ready_Arm, &Pickup_ref);
                SetPwmCcr(CCR_Left_Ready, CCR_Right_Ready, CCR_Middle_Closed, &Pickup_ref);
                SetServoRefFire(Fire_Ready, -Fire_Ready, &Fire_ref);
                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                break;
            case Pickup:
                // 开始取环
                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                SetServoRefFire(Fire_Ready, -Fire_Ready, &Fire_ref);
                switch (Upper_state.Pickup_step) {
                    case Overturn: // 翻转机械臂

                        switch (Upper_state.Pickup_ring) {
                            case First_Ring: // 最上层环

                                SetServoRefPickup(Overturn_Pitch_1, Ready_Yaw, Overture_Arm_1, &Pickup_ref);
                                SetPwmCcr(CCR_Left_Pickup_1, CCR_Right_Pickup_1, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(20);
                                if (hDJI[Motor_id_Pitch].posPID.fdb > Overturn_Pitch_1 && hDJI[Motor_id_Arm].posPID.fdb < Overture_Arm_1) {
                                    PickupSwitchStep(Clamp, &Upper_state);
                                }
                                break;
                            case Second_Ring: // 第二层环

                                SetServoRefPickup(Overturn_Pitch_2, Ready_Yaw, Overture_Arm_2, &Pickup_ref);
                                SetPwmCcr(CCR_Left_Pickup_2, CCR_Right_Pickup_2, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(20);
                                if (hDJI[Motor_id_Pitch].posPID.fdb > Overturn_Pitch_2 && hDJI[Motor_id_Arm].posPID.fdb < Overture_Arm_2) {
                                    PickupSwitchStep(Clamp, &Upper_state);
                                }
                                break;
                            case Third_Ring: // 第三层环
                                SetServoRefPickup(Overturn_Pitch_3, Ready_Yaw, Overture_Arm_3, &Pickup_ref);
                                SetPwmCcr(CCR_Left_Pickup_3, CCR_Right_Pickup_3, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(20);
                                if (hDJI[Motor_id_Pitch].posPID.fdb > Overturn_Pitch_3 && hDJI[Motor_id_Arm].posPID.fdb < Overture_Arm_3) {
                                    PickupSwitchStep(Clamp, &Upper_state);
                                }
                                break;
                            case Fourth_Ring: // 第四层环
                                SetServoRefPickup(Overturn_Pitch_4, Ready_Yaw, Overture_Arm_4, &Pickup_ref);
                                SetPwmCcr(CCR_Left_Pickup_4, CCR_Right_Pickup_4, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(20);
                                if (hDJI[Motor_id_Pitch].posPID.fdb > Overturn_Pitch_4 && hDJI[Motor_id_Arm].posPID.fdb < Overture_Arm_4) {
                                    PickupSwitchStep(Clamp, &Upper_state);
                                }
                                break;
                            case Fifth_Ring: // 第四层环
                                SetServoRefPickup(Overturn_Pitch_5, Ready_Yaw, Overture_Arm_5, &Pickup_ref);
                                SetPwmCcr(CCR_Left_Pickup_5, CCR_Right_Pickup_5, CCR_Middle_Opened, &Pickup_ref);
                                vTaskDelay(20);
                                if (hDJI[Motor_id_Pitch].posPID.fdb > Overturn_Pitch_5 && hDJI[Motor_id_Arm].posPID.fdb < Overture_Arm_5) {
                                    PickupSwitchStep(Clamp, &Upper_state);
                                }
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
                        SetServoRefPickup(Overture_Pitch_back, Ready_Yaw, Overturn_Arm_back, &Pickup_ref);
                        SetPwmCcr(CCR_Left_Ready, CCR_Right_Ready, CCR_Middle_Closed, &Pickup_ref);
                        vTaskDelay(20);
                        if (hDJI[Motor_id_Pitch].posPID.fdb < Overture_Pitch_back && hDJI[Motor_id_Arm].posPID.fdb > Overturn_Arm_back) {
                            PickupSwitchStep(Release, &Upper_state);
                        }
                        break;
                    case Release: // 松开爪子，自动切换到射环
                        SetPwmCcrMiddle(CCR_Middle_Opened, &Pickup_ref);
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
                vPortEnterCritical();
                Fire_point_temp = ChassisData.point; // 获取当前底盘所在点位
                vPortExitCritical();
                switch (Fire_point_temp) // 点位号(预先将点位编号)
                {
                    case 1:
                        switch (Upper_state.Fire_number) // 几号柱子(预先将柱子编号)
                        {
                            case First_Target:
                                SetServoRefPickup(Fire_Pitch_1_1, Fire_Yaw_1_1, Fire_Arm, &Pickup_ref);
                                SetServoRefFire(Fire_1_1, -Fire_1_1, &Fire_ref);
                                vTaskDelay(3000);
                                SetServoRefPush(Fire_Push_Extend, &Fire_ref);
                                vTaskDelay(500);
                                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                                vTaskDelay(500);
                                PickupSwitchState(Ready, &Upper_state);
                                break;
                            case Second_Target:
                                SetServoRefPickup(Fire_Pitch_1_2, Fire_Yaw_1_2, Fire_Arm, &Pickup_ref);
                                SetServoRefFire(Fire_1_2, -Fire_1_2, &Fire_ref);
                                vTaskDelay(3000);
                                SetServoRefPush(Fire_Push_Extend, &Fire_ref);
                                vTaskDelay(500);
                                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                                vTaskDelay(500);
                                PickupSwitchState(Ready, &Upper_state);
                                break;
                            default:
                                break;
                        }
                        break;
                    case 2:
                        switch (Upper_state.Fire_number) {
                            case Third_Target:
                                SetServoRefPickup(Fire_Pitch_2_3, Fire_Yaw_2_3, Fire_Arm, &Pickup_ref);
                                SetServoRefFire(Fire_Pitch_2_3, -Fire_Pitch_2_3, &Fire_ref);
                                vTaskDelay(3000);
                                SetServoRefPush(Fire_Push_Extend, &Fire_ref);
                                vTaskDelay(500);
                                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                                vTaskDelay(500);
                                PickupSwitchState(Ready, &Upper_state);
                                break;
                            case Fourth_Target:
                                SetServoRefPickup(Fire_Pitch_2_4, Fire_Yaw_2_4, Fire_Arm, &Pickup_ref);
                                SetServoRefFire(Fire_Pitch_2_4, -Fire_Pitch_2_4, &Fire_ref);
                                vTaskDelay(3000);
                                SetServoRefPush(Fire_Push_Extend, &Fire_ref);
                                vTaskDelay(500);
                                SetServoRefPush(Fire_Push_Back, &Fire_ref);
                                vTaskDelay(500);
                                PickupSwitchState(Ready, &Upper_state);
                                break;
                            default:
                                break;
                        }
                        break;
                    case 3: // 目前测试只有两个点位
                        switch (Upper_state.Fire_number) {
                            case Third_Target:
                                break;
                            case Fourth_Target:
                                break;
                            default:
                                break;
                        }
                        break;
                    case 4:
                        switch (Upper_state.Fire_number) {
                            case Fourth_Target:
                                break;
                            case Fifth_Target:
                                break;
                            default:
                                break;
                        }
                        break;
                    case 5:
                        switch (Upper_state.Fire_number) {
                            case Fourth_Target:
                                break;
                            case Fifth_Target:
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
        osDelay(1);
    }
}

void StateMachineTestTask(void const *argument)
{
    osDelay(2);
    for (;;) {
        osDelay(2);
    }
}

void StateMachineTaskStart(mavlink_controller_t *controldata)
{
    // osThreadDef(StateMachine, StateMachineTask, osPriorityNormal, 0, 512);
    // osThreadCreate(osThread(StateMachine), controldata);

    osThreadDef(upper_rr_test, StateMachineTestTask, osPriorityBelowNormal, 0, 512);
    osThreadCreate(osThread(upper_rr_test), NULL);
}
