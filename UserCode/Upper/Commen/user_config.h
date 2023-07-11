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

/********************初始状态*********************/
#define Ready_Pitch 0
#define Ready_Yaw   0
#define Ready_Arm   0

/*********************抱着环*********************/
#define Hug_Pitch      543
#define Hug_Yaw        0
#define Hug_Arm        -227

#define Hug_CCR_Left   2100
#define Hug_CCR_Right  1100
#define Hug_CCR_Middle 1740

/***********************取环*********************/
#define Overturn_Pitch_1    78
#define Overturn_Pitch_2    84
#define Overturn_Pitch_3    92
#define Overturn_Pitch_4    265
#define Overturn_Pitch_5    310
#define Overturn_Pitch_6    356
#define Overturn_Pitch_7    403
#define Overturn_Pitch_8    450
#define Overturn_Pitch_9    498
#define Overturn_Pitch_10   545

#define Overture_Arm_1      -263
#define Overture_Arm_2      -260
#define Overture_Arm_3      -257
#define Overture_Arm_4      -261
#define Overture_Arm_5      -259
#define Overture_Arm_6      -255
#define Overture_Arm_7      -252
#define Overture_Arm_8      -249
#define Overture_Arm_9      -246
#define Overture_Arm_10     -243

#define Overture_Pitch_back 150
#define Overturn_Arm_back   0
#define Pickup_Yaw          0

// 过度
#define Overturn_Pitch_Transition -420
#define Overturn_Yaw_Transition   0
#define Overturn_Arm_Transition   -155
#define CCR_Left_Transition       1200
#define CCR_Right_Transition      1950

// 舵机
#define CCR_Middle_Ready    2000
#define CCR_Middle_Closed   1950 //? 夹紧
#define CCR_Middle_Opened   1350 // 张开

#define CCR_Left_Ready      1720
#define CCR_Left_Pickup_1   1380
#define CCR_Left_Pickup_2   1380
#define CCR_Left_Pickup_3   1380
#define CCR_Left_Pickup_4   1340
#define CCR_Left_Pickup_5   1340
#define CCR_Left_Pickup_6   1340
#define CCR_Left_Pickup_7   1340
#define CCR_Left_Pickup_8   1340
#define CCR_Left_Pickup_9   1340
#define CCR_Left_Pickup_10  1340

#define CCR_Right_Ready     1460
#define CCR_Right_Pickup_1  1820
#define CCR_Right_Pickup_2  1820
#define CCR_Right_Pickup_3  1820
#define CCR_Right_Pickup_4  1860
#define CCR_Right_Pickup_5  1860
#define CCR_Right_Pickup_6  1860
#define CCR_Right_Pickup_7  1860
#define CCR_Right_Pickup_8  1860
#define CCR_Right_Pickup_9  1860
#define CCR_Right_Pickup_10 1860

/*********************射环准备状态***********************/
#define Fire_Ready_Pitch 300
#define Fire_Ready_Yaw 0
#define Fire_Ready_Arm -75

#define Fire_Ready_CCR_Left 1900
#define Fire_Ready_CCR_Right 1300
#define Fire_Ready_CCR_Middle 1600

/*********************射环***********************/
//射速
#define Fire_Ready       0
#define Fire_Accelerate 1500
#define Fire_3_1         1750
#define Fire_3_2         0
#define Fire_3_3         1600

#define Fire_4_1         0
#define Fire_4_2         1750
#define Fire_4_3         0

#define Fire_5_1         2336
#define Fire_5_2         2336
#define Fire_5_3         2176
#define Fire_5_4         1756
#define Fire_5_5         1756
#define Fire_5_6         2100
#define Fire_5_7         1300
#define Fire_5_8         2100

#define Fire_6_1         0
#define Fire_6_2         1600
#define Fire_6_3         0
#define Fire_6_4         0
#define Fire_6_5         1600
#define Fire_6_6         0
#define Fire_6_7         0
#define Fire_6_8         1600

#define Fire_7_1         0
#define Fire_7_2         1600
#define Fire_7_3         0
#define Fire_7_4         0
#define Fire_7_5         1600
#define Fire_7_6         0
#define Fire_7_7         0
#define Fire_7_8         1600

// pitch
#define Fire_Pitch_3_1   125
#define Fire_Pitch_3_2   0
#define Fire_Pitch_3_3   115

#define Fire_Pitch_4_1   0
#define Fire_Pitch_4_2   125
#define Fire_Pitch_4_3   0

#define Fire_Pitch_5_1   300
#define Fire_Pitch_5_2   300
#define Fire_Pitch_5_3   515
#define Fire_Pitch_5_4   350
#define Fire_Pitch_5_5   350
#define Fire_Pitch_5_6   270
#define Fire_Pitch_5_7   390
#define Fire_Pitch_5_8   270

#define Fire_Pitch_6_1   0
#define Fire_Pitch_6_2   115
#define Fire_Pitch_6_3   0
#define Fire_Pitch_6_4   0
#define Fire_Pitch_6_5   115
#define Fire_Pitch_6_6   0
#define Fire_Pitch_6_7   0
#define Fire_Pitch_6_8   115

#define Fire_Pitch_7_1   0
#define Fire_Pitch_7_2   115
#define Fire_Pitch_7_3   0
#define Fire_Pitch_7_4   0
#define Fire_Pitch_7_5   115
#define Fire_Pitch_7_6   0
#define Fire_Pitch_7_7   0
#define Fire_Pitch_7_8   115

//Yaw
#define Fire_Yaw_3_1     0
#define Fire_Yaw_3_2     0
#define Fire_Yaw_3_3     0

#define Fire_Yaw_4_1     0
#define Fire_Yaw_4_2     0
#define Fire_Yaw_4_3     0

#define Fire_Yaw_5_1     0
#define Fire_Yaw_5_2     0
#define Fire_Yaw_5_3     0
#define Fire_Yaw_5_4     0
#define Fire_Yaw_5_5     0
#define Fire_Yaw_5_6     0
#define Fire_Yaw_5_7     0
#define Fire_Yaw_5_8     0

#define Fire_Yaw_6_1     0
#define Fire_Yaw_6_2     0
#define Fire_Yaw_6_3     0
#define Fire_Yaw_6_4     0
#define Fire_Yaw_6_5     0
#define Fire_Yaw_6_6     0
#define Fire_Yaw_6_7     0
#define Fire_Yaw_6_8     0

#define Fire_Yaw_7_1     0
#define Fire_Yaw_7_2     0
#define Fire_Yaw_7_3     0
#define Fire_Yaw_7_4     0
#define Fire_Yaw_7_5     0
#define Fire_Yaw_7_6     0
#define Fire_Yaw_7_7     0
#define Fire_Yaw_7_8     0

#define Fire_Arm         -75
#define Fire_Push_Extend 65
#define Fire_Push_Back   0

#define Fire_CCR_Left    1900
#define Fire_CCR_Right   1300
#define Fire_CCR_Middle  1600

#define Fire_Wheel_Ratio 0.875

/**************电机的最大角速度 角加速度*************/
#define MaxAngularVelocity_Pitch       6000
#define MaxAngularVelocity_Arm         600
#define MaxAngularVelocity_Yaw         2500
#define MaxAngularVelocity_CCR         550

#define MotorAngularAcceleration_Pitch 4500
#define MotorAngularAcceleration_Arm   600
#define MotorAngularAcceleration_Yaw   1000

/**
 * @brief id
 *
 */
#define Motor_id_Fire_Left_Small  7
#define Motor_id_Fire_Left_Large  1
#define Motor_id_Fire_Right_Large 6
#define Motor_id_Fire_Right_Small 3
#define Motor_id_Push             2
#define Motor_id_Pitch            4
#define Motor_id_Arm              5
#define Motor_id_Yaw              0

/**
 * @brief 端口
 *
 */
#define htim_claw_left              htim8
#define htim_claw_right             htim8
#define htim_claw_middle            htim8
#define huart_Mavlink               huart6
#define huart_AS69                  huart1
#define TIM_CHANNEL_CLAW_LEFT       TIM_CHANNEL_1
#define TIM_CHANNEL_CLAW_RIGHT      TIM_CHANNEL_2
#define TIM_CHANNEL_CLAW_MIDDLE     TIM_CHANNEL_3
#define USART_MAVLINK               USART6
#define USART_DJI_REMOTE_CONTROLLER USART1

#define Ongoing                     1
#define Finished                    0
#define OverturnAngle               (-728 - 1)
