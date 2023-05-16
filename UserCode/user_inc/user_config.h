/***
 * @Author: Xieyang
 * @Date: 2023-02-23 18:51:00
 * @LastEditTime: 2023-05-11 21:47:41
 * @LastEditors: szf
 * @Description: 端口定义、id定义、常量定义
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\user_config.h
 * @@WeChat:szf13373959031
 */

#pragma once
/**
 * @brief 一些有用的常量，基本上是从 GCC 的 math.h 中复制下来的(因为 ARMCC 的库里貌似没有)
 *
 */

#define _M_LN2     0.693147180559945309417 // Natural log of 2

#define MAXFLOAT   3.40282347e+38F

#define M_E        2.7182818284590452354
#define M_LOG2E    1.4426950408889634074
#define M_LOG10E   0.43429448190325182765
#define M_LN2      _M_LN2
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846

#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.78539816339744830962
#define M_1_PI     0.31830988618379067154
#define M_2_PI     0.63661977236758134308
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.70710678118654752440

#define M_TWOPI    (M_PI * 2.0)
#define M_3PI_4    2.3561944901923448370E0
#define M_SQRTPI   1.77245385090551602792981
#define M_LN2LO    1.9082149292705877000E-10
#define M_LN2HI    6.9314718036912381649E-1
#define M_SQRT3    1.73205080756887719000
#define M_IVLN10   0.43429448190325182765 /* 1 / log(10) */
#define M_LOG2_E   _M_LN2
#define M_INVLN2   1.4426950408889633870E0 /* 1 / log(2) */

/**
 * @brief 参数
 *
 */

// 初始状态
#define Ready_Pitch 0
#define Ready_Yaw   0
#define Ready_Arm   0

// 取环(5种)过程
#define Overturn_Pitch_1    156
#define Overturn_Pitch_2    156
#define Overturn_Pitch_3    156
#define Overturn_Pitch_4    156
#define Overturn_Pitch_5    156

#define Overture_Arm_1      -210
#define Overture_Arm_2      -210
#define Overture_Arm_3      -210
#define Overture_Arm_4      -210
#define Overture_Arm_5      -210

#define Overture_Pitch_back 90
#define Overturn_Arm_back   0

// 三个舵机
#define CCR_Middle_Closed  0
#define CCR_Middle_Opened  0

#define CCR_Left_Ready     0
#define CCR_Left_Pickup_1  0
#define CCR_Left_Pickup_2  0
#define CCR_Left_Pickup_3  0
#define CCR_Left_Pickup_4  0
#define CCR_Left_Pickup_5  0

#define CCR_Right_Ready    0
#define CCR_Right_Pickup_1 0
#define CCR_Right_Pickup_2 0
#define CCR_Right_Pickup_3 0
#define CCR_Right_Pickup_4 0
#define CCR_Right_Pickup_5 0

// 射环
#define Fire_Ready       0
#define Fire_1_1         0
#define Fire_1_2         0
#define Fire_2_3         0
#define Fire_2_4         0

#define Fire_Pitch_1_1   0
#define Fire_Pitch_1_2   0
#define Fire_Pitch_2_3   0
#define Fire_Pitch_2_4   0 //? 俯仰是否要定死

#define Fire_Yaw_1_1     0
#define Fire_Yaw_1_2     0
#define Fire_Yaw_2_3     0
#define Fire_Yaw_2_4     0

#define Fire_Arm         -30
#define Fire_Push_Extend 73
#define Fire_Push_Back   0

// 电机的最大角速度 角加速度
#define MaxAngularVelocity_Pitch 0.5
#define MaxAngularVelocity_Arm 0.5
#define MaxAngularVelocity_Yaw 0.5

#define MotorAngularAcceleration 0.1
/**
 * @brief id
 *
 */
#define Motor_id_Fire_Left  0
#define Motor_id_Fire_Right 1
#define Motor_id_Push       2
#define Motor_id_Pitch      4
#define Motor_id_Arm        5
#define Motor_id_Yaw        6


/**
 * @brief 端口
 *
 */
#define htim_claw_left htim8
#define htim_claw_right htim8
#define htim_claw_middle htim8
#define TIM_CHANNEL_CLAW_LEFT TIM_CHANNEL_1
#define TIM_CHANNEL_CLAW_RIGHT TIM_CHANNEL_2
#define TIM_CHANNEL_CLAW_MIDDLE TIM_CHANNEL_3
#define USART_MAVLINK USART2
#define USART_DJI_REMOTE_CONTROLLER USART1

