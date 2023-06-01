#ifndef __CHASSIS_REMOTE_CONTROL__
#define __CHASSIS_REMOTE_CONTROL__

#include "wtr_mavlink.h"

typedef enum {
    Left_switch = 0,
    Right_switch
} SWITCHS;

typedef enum {
    Btn_LeftCrossUp     = 2,
    Btn_LeftCrossDown   = 1,
    Btn_LeftCrossLeft   = 13,
    Btn_LeftCrossRight  = 5,
    Btn_LeftCrossMid    = 9,
    Btn_RightCrossUp    = 4,
    Btn_RightCrossDown  = 3,
    Btn_RightCrossLeft  = 7,
    Btn_RightCrossRight = 15,
    Btn_RightCrossMid   = 11,
    Btn_Btn0            = 6,
    Btn_Btn1            = 10,
    Btn_Btn2            = 14,
    Btn_Btn3            = 8,
    Btn_Btn4            = 12,
    Btn_Btn5            = 16,
    Btn_KnobL           = 17,
    Btn_KnobR           = 18,
    Btn_JoystickL       = 19,
    Btn_JoystickR       = 20,
} KEYS;

bool ReadJoystickButtons(mavlink_joystick_air_t msg_joystick_air_, KEYS index);
float ReadJoystickLeft_x(mavlink_joystick_air_t msg_joystick_air_);
float ReadJoystickLeft_y(mavlink_joystick_air_t msg_joystick_air_);
float ReadJoystickRight_x(mavlink_joystick_air_t msg_joystick_air_);
float ReadJoystickRight_y(mavlink_joystick_air_t msg_joystick_air_);
int16_t ReadJoystickKnobsLeft_x(mavlink_joystick_air_t msg_joystick_air_);
int16_t ReadJoystickKnobsLeft_y(mavlink_joystick_air_t msg_joystick_air_);
bool ReadJoystickSwitchs(mavlink_joystick_air_t msg_joystick_air_, SWITCHS index);

extern mavlink_joystick_air_t msg_joystick_air;

#endif