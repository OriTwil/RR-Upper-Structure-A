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
#include "upper_pick_up.h"

Button button = 
{
    .button_min_time = 500,
    .last_tick       = 0,
};

PICKUP_STATE Pickup_state = Ready;
PICKUP_STEP Pickup_step = Overturn;
PICKUP_NUMBER pickup_number = First_Point;
FIRE_NUMBER fire_number = First_Target;

void rrPickUpTask(void const *argument)
{
    const mavlink_controller_t *ctrl_data = argument;
    osDelay(200);

    for (;;) 
	{
        if (ctrl_data->buttons & (1 << 6)) 
		{
            if (button.last_tick + button.button_min_time < HAL_GetTick()) 
			{
                button.last_tick = HAL_GetTick();
        	}
    	}
		switch(Pickup_state)
		{
			case Ready:
				// 锁死在初始状态
				break;
			case Pickup:
				// 开始取环
				switch(Pickup_step)
				{
					case Overturn:
						switch(pickup_number)
						{
							case First_Point:
								break;
							case Second_Point:
								break;
							case Third_Point:
								break;
							case Fourth_Point:
								break;
							case Fifth_Point:
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
				break;
			default:
				break;
		}
		osDelay(1);
	}
}

void rrPickUpTestTask(void const *argument)
{
	osDelay(2);	
	for(;;)
	{
		CanTransmit_DJI_5678(&hcan1,
				hDJI[4].speedPID.output,
				hDJI[5].speedPID.output,
				hDJI[6].speedPID.output,
				hDJI[7].speedPID.output);
	}
	osDelay(1);
	
}

void PickUpTaskStart(mavlink_controller_t *controldata)
{
    // osThreadDef(rrpickup, rrPickUpTask, osPriorityNormal, 0, 512);
    // osThreadCreate(osThread(rrpickup), controldata);

	osThreadDef(upper_rr_test, rrPickUpTestTask, osPriorityNormal, 0, 512);
    osThreadCreate(osThread(upper_rr_test), NULL);
}

void DeadBand(double x, double y, double *new_x, double *new_y, double threshould)
{
    double length     = sqrt(x * x + y * y);
    double new_length = length - threshould;

    if (new_length <= 0) {
        *new_x = 0;
        *new_y = 0;
        return;
    }

    double k = new_length / length;

    *new_x = x * k;
    *new_y = y * k;
}
