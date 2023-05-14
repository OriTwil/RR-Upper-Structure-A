/*
 * @Author: szf
 * @Date: 2023-03-08 19:12:32
 * @LastEditTime: 2023-05-11 19:36:09
 * @LastEditors: szf
 * @Description:取环的线程
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\upper_pick_up.c
 * @WeChat:szf13373959031
 */

#include "wtr_uart.h"
#include "tim.h"
#include "upper_state_machine.h"

void StateMachineTask(void const *argument)
{
    const mavlink_controller_t *ctrl_data = argument;
    osDelay(200);

    for (;;) 
	{
		switch(Upper_state.Pickup_state)
		{
			case Ready:
				// 锁死在初始状态
				break;
			case Pickup:
				// 开始取环
				switch(Upper_state.Pickup_step)
				{
					case Overturn:
						switch(Upper_state.Pickup_ring)
						{
							case First_Ring:
								break;
							case Second_Ring:
								break;
							case Third_Ring:
								break;
							case Fourth_Ring:
								break;
							case Fifth_Ring:
								break;
							default:
								break;
						}
						break;
					case Clamp:
						break;
					case Pitch_Overturn_back:
						break;
					case Arm_Overturn_back:
						break;
					case Release:
						break;
					default:
						break;
				}
				break;
			case Fire:
				// 射环
				switch(Upper_state.Pickup_ring)
				{
					case First_Ring:
						switch(Upper_state.Fire_number)
						{
							case First_Target:
								break;
							case Second_Target:
								break;
							default:
								break;
						}
						break;
					case Second_Ring:
						switch(Upper_state.Fire_number)
						{
							case Second_Target:
								break;
							case Third_Target:
								break;
							default:
								break;
						}
						break;
					case Third_Ring:
						switch(Upper_state.Fire_number)
						{
							case Third_Target:
								break;
							case Fourth_Target:
								break;
							default:
								break;
						}
						break;
					case Fourth_Ring:
						switch(Upper_state.Fire_number)
						{
							case Fourth_Target:
								break;
							case Fifth_Target:
								break;
							default:
								break;
						}
						break;
					case Fifth_Ring:
						switch(Upper_state.Fire_number)
						{
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
	for(;;)
	{
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


