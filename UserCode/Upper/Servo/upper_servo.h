/*** 
 * @Author: szf
 * @Date: 2023-03-11 12:51:24
 * @LastEditTime: 2023-05-11 16:02:24
 * @LastEditors: szf
 * @Description: 以固定频率进行伺服
 * @FilePath: \RR-Upper-Structure-A\UserCode\user_inc\upper_servo.h
 * @@WeChat:szf13373959031
 */
#ifndef UPPER_SERVO_H
#define UPPER_SERVO_H

#include "upper_state_machine.h"
#include "upper_start.h"
#include "math.h"
#include "upper_commen.h"
#include "user_config.h"

void ServoTaskStart();
void MotorInit();
void PWMInit();

void SetServoRefPickup(float ref_pitch, float ref_yaw, float ref_arm, SERVO_REF_PICKUP *current_servo_ref);

void SetPwmCcr(int pwm_ccr_left, int pwm_ccr_right, int pwm_ccr_middle, SERVO_REF_PICKUP *current_servo_ref);

void SetServoRefFire(float ref_left, float ref_right, SERVO_REF_FIRE *current_fire_ref);

void SetPwmCcrMiddle(int pwm_ccr_middle, SERVO_REF_PICKUP *current_pickup_ref);

void SetServoRefPush(float ref_push, SERVO_REF_FIRE *current_fire_ref);

void VelocityPlanning(float initialAngle, float maxAngularVelocity, float AngularAcceleration, float targetAngle, float currentTime, __IO float *currentAngle);

void SetServoRefPickupTrajectory(float ref_pitch, float ref_yaw, float ref_arm, SERVO_REF_PICKUP *current_pickup_ref);

void SetPwmCcrMiddleTrajectory(int pwm_ccr_middle, SERVO_REF_PICKUP *current_pickup_ref);

extern SERVO_REF_PICKUP Pickup_ref;
extern SERVO_REF_FIRE Fire_ref;

#endif