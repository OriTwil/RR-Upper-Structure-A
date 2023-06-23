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
#define Hug_Pitch 160
#define Hug_Yaw   0
#define Hug_Arm   -217

#define Hug_CCR_Left 2100
#define Hug_CCR_Right 1100
#define Hug_CCR_Middle 1800

/***********************取环*********************/
#define Overturn_Pitch_1    78
#define Overturn_Pitch_2    84
#define Overturn_Pitch_3    92
#define Overturn_Pitch_4    102
#define Overturn_Pitch_5    110
#define Overturn_Pitch_6    119
#define Overturn_Pitch_7    128
#define Overturn_Pitch_8    136
#define Overturn_Pitch_9    145
#define Overturn_Pitch_10   156

#define Overture_Arm_1      -268
#define Overture_Arm_2      -268
#define Overture_Arm_3      -266
#define Overture_Arm_4      -266
#define Overture_Arm_5      -262
#define Overture_Arm_6      -256
#define Overture_Arm_7      -256
#define Overture_Arm_8      -252
#define Overture_Arm_9      -246
#define Overture_Arm_10     -242

#define Overture_Pitch_back 90
#define Overturn_Arm_back   0
#define Pickup_Yaw          0

// 过度
#define Overturn_Pitch_Transition 30
#define Overturn_Yaw_Transition   0
#define Overturn_Arm_Transition   -250
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
#define CCR_Left_Pickup_4   1380
#define CCR_Left_Pickup_5   1380
#define CCR_Left_Pickup_6   1360
#define CCR_Left_Pickup_7   1360
#define CCR_Left_Pickup_8   1350
#define CCR_Left_Pickup_9   1350
#define CCR_Left_Pickup_10  1350

#define CCR_Right_Ready     1460
#define CCR_Right_Pickup_1  1820
#define CCR_Right_Pickup_2  1820
#define CCR_Right_Pickup_3  1820
#define CCR_Right_Pickup_4  1820
#define CCR_Right_Pickup_5  1820
#define CCR_Right_Pickup_6  1850
#define CCR_Right_Pickup_7  1850
#define CCR_Right_Pickup_8  1860
#define CCR_Right_Pickup_9  1860
#define CCR_Right_Pickup_10 1860

/*********************射环***********************/
#define Fire_Ready       0
#define Fire_3_1         1750 
#define Fire_3_2         0    
#define Fire_3_3         1600   
#define Fire_4_1         0 
#define Fire_4_2         1750 
#define Fire_4_3         0    
#define Fire_5_1         1600   
#define Fire_5_2         0 
#define Fire_5_3         1750 
#define Fire_6_1         0    
#define Fire_6_2         1600   
#define Fire_6_3         0 

#define Fire_Pitch_3_1   125
#define Fire_Pitch_3_2   0
#define Fire_Pitch_3_3   115
#define Fire_Pitch_4_1   0
#define Fire_Pitch_4_2   125
#define Fire_Pitch_4_3   0
#define Fire_Pitch_5_1   115
#define Fire_Pitch_5_2   0
#define Fire_Pitch_5_3   125
#define Fire_Pitch_6_1   0
#define Fire_Pitch_6_2   115
#define Fire_Pitch_6_3   0

#define Fire_Yaw_3_1     0
#define Fire_Yaw_3_2     0
#define Fire_Yaw_3_3     0
#define Fire_Yaw_4_1     0
#define Fire_Yaw_4_2     0
#define Fire_Yaw_4_3     0
#define Fire_Yaw_5_1     0
#define Fire_Yaw_5_2     0
#define Fire_Yaw_5_3     0
#define Fire_Yaw_6_1     0
#define Fire_Yaw_6_2     0
#define Fire_Yaw_6_3     0

#define Fire_Arm         -40
#define Fire_Push_Extend 60
#define Fire_Push_Back   0

#define Fire_CCR_Left 1900
#define Fire_CCR_Right 1300 
#define Fire_CCR_Middle 1600

#define Fire_Wheel_Ratio 0.875

/**************电机的最大角速度 角加速度*************/
#define MaxAngularVelocity_Pitch 500
#define MaxAngularVelocity_Arm   300
#define MaxAngularVelocity_Yaw   2500
#define MaxAngularVelocity_CCR   380

#define MotorAngularAcceleration_Pitch 500
#define MotorAngularAcceleration_Arm  300
#define MotorAngularAcceleration_Yaw  1000
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
