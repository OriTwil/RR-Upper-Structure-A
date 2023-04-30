/*
 * @Author: szf
 * @Date: 2023-03-08 19:12:32
 * @LastEditTime: 2023-04-30 19:39:25
 * @LastEditors: szf
 * @Description:
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_src\pick_up.c
 * @WeChat:szf13373959031
 */

#include "wtr_uart.h"
#include "tim.h"
#include "pick_up.h"

Button button = {
    .button_min_time = 500,
    .last_tick       = 0,
};

bool Pickup_state = Finished;
Mode Pickup_mode = Motionless;


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
				Pickup_state = Ongoing;
				Pickup_mode = Overturn;
        	}
    	}
		osDelay(1);
	}
}


void rrPickUpTestTask(void const *argument)
{
	Pickup_state = Ongoing;
	Pickup_mode = Overturn;

	static int clockClamp = 0;
	static int clockRelease = 0;
	osDelay(2);	
	for(;;)
	{
		if(Pickup_state == Finished)
		{
			CanTransmit_DJI_5678(&hcan1,
			hDJI[4].speedPID.output,
			hDJI[5].speedPID.output,
			hDJI[6].speedPID.output,
			hDJI[7].speedPID.output);
		}
		else if(Pickup_state == Ongoing) // 开始取环
		{
			switch(Pickup_mode)
			{
				case Motionless:
					Pickup_state = Finished;  
					osDelay(1);
					break;
				case Overturn:
					if(hDJI[4].posPID.fdb >= Overturn_Pitch - 1 && hDJI[5].posPID.fdb <= Overture_Arm + 1)
					{
						Pickup_mode = Clamp;
					}
					osDelay(1);
					break;
				case Clamp:
					if(clockClamp++ > 1000)
					{
						clockClamp = 0;
						Pickup_mode = Pitch_Overturn_back;
					}
					osDelay(1);
					break;
				case Pitch_Overturn_back:
					if(hDJI[4].posPID.fdb < Overture_Pitch_back + 1)
					{
						Pickup_mode = Arm_Overturn_back;
					}
					osDelay(1);
					break;
				case Arm_Overturn_back:
					if(hDJI[5].posPID.fdb > Overturn_Arm_back - 1)
					{
						Pickup_mode = Release;
					}
					osDelay(1);
					break;
				case Release:
					if(clockRelease++ >= 1000)
					{
						Pickup_mode = Fire;
						clockRelease = 0;
					}
					osDelay(1);
					break;
				case Fire:
					if((hDJI[5].posPID.fdb < Fire_Arm + 1) && (hDJI[6].posPID.fdb > Fire_Angle - 1))
					{
						Pickup_mode = Motionless;
					}
					osDelay(1);
					break;
					
			}
			CanTransmit_DJI_5678(&hcan1,
					hDJI[4].speedPID.output,
					hDJI[5].speedPID.output,
					hDJI[6].speedPID.output,
					hDJI[7].speedPID.output);
		}
		osDelay(1);
	
	}
}


void PickUpTaskStart(mavlink_controller_t *controldata)
{
    // osThreadDef(rrpickup, rrPickUpTask, osPriorityBelowNormal, 0, 512);
    // osThreadCreate(osThread(rrpickup), controldata);

	osThreadDef(upper_rr_test, rrPickUpTestTask, osPriorityBelowNormal, 0, 512);
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
