/**
 * @file user_caculate.c
 * @author WTR
 * @brief 算法函数
 * @version
 * @date 2023.5.14
 *
 */

#include "user_caculate.h"
#include "math.h"

// 增量式PID算法
void PID_Calc(PID_t *pid)
{
    pid->cur_error = pid->ref - pid->fdb;
    pid->output += pid->KP * (pid->cur_error - pid->error[1]) + pid->KI * pid->cur_error + pid->KD * (pid->cur_error - 2 * pid->error[1] + pid->error[0]);
    pid->error[0] = pid->error[1];
    pid->error[1] = pid->ref - pid->fdb;
    /*设定输出上限*/
    if (pid->output > pid->outputMax) pid->output = pid->outputMax;
    if (pid->output < -pid->outputMax) pid->output = -pid->outputMax;
}

// 比例算法
void P_Calc(PID_t *pid)
{
    pid->cur_error = pid->ref - pid->fdb;
    pid->output    = pid->KP * pid->cur_error;
    /*设定输出上限*/
    if (pid->output > pid->outputMax) pid->output = pid->outputMax;
    if (pid->output < -pid->outputMax) pid->output = -pid->outputMax;

    if (fabs(pid->output) < pid->outputMin)
        pid->output = 0;
}

// 位置伺服函数
void positionServo(float ref, DJI_t *motor)
{

    motor->posPID.ref = ref;
    motor->posPID.fdb = motor->AxisData.AxisAngle_inDegree;
    PID_Calc(&motor->posPID);

    motor->speedPID.ref = motor->posPID.output;
    motor->speedPID.fdb = motor->FdbData.rpm;
    PID_Calc(&motor->speedPID);
}

// 速度伺服函数
void speedServo(float ref, DJI_t *motor)
{
    motor->speedPID.ref = ref;
    motor->speedPID.fdb = motor->FdbData.rpm;
    PID_Calc(&motor->speedPID);
}

// 死区(用于摇杆)
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
