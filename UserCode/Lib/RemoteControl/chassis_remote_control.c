// #include "portmacro.h"
#include "chassis_remote_control.h"
#include "wtr_mavlink.h"
#include "wtr_uart.h"

mavlink_joystick_air_t msg_joystick_air;

bool ReadJoystickButtons(mavlink_joystick_air_t msg_joystick_air_, KEYS index)
{
    vPortEnterCritical();
    mavlink_joystick_air_t msg_joystick_air_temp = msg_joystick_air_;
    vPortExitCritical();

    return ((msg_joystick_air_temp.buttons >> (index - 1)) & 1);
}

float ReadJoystickLeft_x(mavlink_joystick_air_t msg_joystick_air_)
{
    vPortEnterCritical();
    mavlink_joystick_air_t msg_joystick_air_temp = msg_joystick_air_;
    vPortExitCritical();
    return msg_joystick_air_temp.joystickL[0];
}

float ReadJoystickLeft_y(mavlink_joystick_air_t msg_joystick_air_)
{
    vPortEnterCritical();
    mavlink_joystick_air_t msg_joystick_air_temp = msg_joystick_air_;
    vPortExitCritical();
    return msg_joystick_air_temp.joystickL[1];
}

float ReadJoystickRight_x(mavlink_joystick_air_t msg_joystick_air_)
{
    vPortEnterCritical();
    mavlink_joystick_air_t msg_joystick_air_temp = msg_joystick_air_;
    vPortExitCritical();
    return msg_joystick_air_temp.joystickR[0];
}

float ReadJoystickRight_y(mavlink_joystick_air_t msg_joystick_air_)
{
    vPortEnterCritical();
    mavlink_joystick_air_t msg_joystick_air_temp = msg_joystick_air_;
    vPortExitCritical();
    return msg_joystick_air_temp.joystickR[1];
}

int16_t ReadJoystickKnobsLeft_x(mavlink_joystick_air_t msg_joystick_air_)
{
    vPortEnterCritical();
    mavlink_joystick_air_t msg_joystick_air_temp = msg_joystick_air_;
    vPortExitCritical();

    return msg_joystick_air_temp.knobs[0];
}

int16_t ReadJoystickKnobsLeft_y(mavlink_joystick_air_t msg_joystick_air_)
{
    vPortEnterCritical();
    mavlink_joystick_air_t msg_joystick_air_temp = msg_joystick_air_;
    vPortExitCritical();

    return msg_joystick_air_temp.knobs[1];
}

bool ReadJoystickSwitchs(mavlink_joystick_air_t msg_joystick_air_, SWITCHS index)
{
    vPortEnterCritical();
    mavlink_joystick_air_t msg_joystick_air_temp = msg_joystick_air_;
    vPortExitCritical();
    return ((msg_joystick_air_temp.switchs >> index) & 1);
}