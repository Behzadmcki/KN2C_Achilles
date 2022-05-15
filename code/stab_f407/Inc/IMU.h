#ifndef H_IMU_H
#define H_IMU_H
#include "main.h"
#include "stm32f4xx_hal.h"
#include "math.h"
#include "mpu6050.h"
//#include "Define.h"

//typedef struct _MPU_SENSOR MPU_SENSOR;

//*********************************************************
#define Mahony_twoKpDef        (2.0f * 1.7f)   // 2 * proportional gain
#define Mahony_twoKiDef        (2.0f * 0.5f)   // 2 * integral gain


//*********************************************************

 typedef struct{
	 
	
	 float q0,q1,q2,q3;
	 
	 float Roll,Pitch,Yaw;
	 float last_Yaw,last_Pitch,last_Roll;
	 float Twokp_Y;
	 
	 
	 float integralFBx,integralFBy,integralFBz;
	  
	 float Accel_weight;
	 
	 float pure_acc_x,pure_acc_y,pure_acc_z;
	 
	 float Y_twokp;
	 float Earth_acc_x,Earth_acc_y,Earth_acc_z;
	 
	 int   yaw_flag_for_return;
	 float diff_yaw;
	 	 
}_IMU;


 
extern _IMU Mahony;
extern _IMU Mahony_ODO;


//*********************************************************

void Update_IMU_Data_Mahony(_IMU *IMU,MPU_SENSOR *sen);
void MahonyAHRSupdateIMU(_IMU *IMU,MPU_SENSOR *sen);

void update_Accel_weight(_IMU *IMU,MPU_SENSOR *sen);
void Update_Euler_angles(_IMU *IMU,MPU_SENSOR *sen);
void Calculate_Static_Acc(_IMU *IMU,MPU_SENSOR *sen);


float invSqrt(float x);










#endif 

