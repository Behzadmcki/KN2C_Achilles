#include "IMU.h"
//#include "Control.h"

_IMU Mahony;
_IMU Mahony_ODO;

float temp;


void Update_IMU_Data_Mahony(_IMU *IMU,MPU_SENSOR *sen)
{
	//HAL_NVIC_DisableIRQ(DMA1_Stream2_IRQn);
	Mpu_update(sen);   //Alireza: update gyro & acc & gravity
	//HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
	update_Accel_weight(IMU,sen);
	MahonyAHRSupdateIMU(IMU,sen);
	Update_Euler_angles(IMU,sen);
	
	
}


void update_Accel_weight(_IMU *IMU,MPU_SENSOR *sen)
{

    sen->Accel_magnitude = sqrt(sen->acc_x*sen->acc_x + sen->acc_y * sen->acc_y + sen->acc_z * sen->acc_z);
  
    sen->Accel_magnitude = sen->Accel_magnitude / sen->Gravity; 
    sen->g_print=fabs(fabs(1.0f-sen->Accel_magnitude ));


    sen->g_print=sen->last_g_print+(DT / ( FILTER_G_PRINT + DT)) * (sen->g_print-sen->last_g_print-0.00000001);                
              
    sen->last_g_print=sen->g_print;  
	
//																	if ( Yaw.flag == 0 ){    // moj

																	if(sen->g_print < 0.016f)
																						IMU->Accel_weight=1.2f;  
																	else if(sen->g_print < 0.019f)
																						IMU->Accel_weight=0.8f;          
																	else if(sen->g_print < 0.027f)
																						IMU->Accel_weight=0.25f; 
																	else if(sen->g_print < 0.029f)
																						IMU->Accel_weight=0.05f; 
																	else if(sen->g_print < 0.031f)
																						IMU->Accel_weight=0.005f; 
																	else if(sen->g_print < 0.5f)
																						IMU->Accel_weight=0.00005f;      
																	else if(sen->g_print < 0.6f)
																						IMU->Accel_weight=0.000001f;
																	else
																						IMU->Accel_weight=0.0000001f;
//																}		
//	if (Yaw.flag == 1){         // moj
		
//																			if(sen->g_print < 0.006f)
//																								IMU->Accel_weight=1.2f;  
//																			else if(sen->g_print < 0.009f)
//																								IMU->Accel_weight=0.8f;          
//																			else if(sen->g_print < 0.014f)
//																								IMU->Accel_weight=0.25f; 
//																			else if(sen->g_print < 0.018f)
//																								IMU->Accel_weight=0.05f; 
//																			else if(sen->g_print < 0.021f)
//																								IMU->Accel_weight=0.005f; 
//																			else if(sen->g_print < 0.023f)
//																								IMU->Accel_weight=0.00005f;      
//																			else if(sen->g_print < 0.026f)
//																								IMU->Accel_weight=0.000001f;
//																			else
//																								IMU->Accel_weight=0.0000001f;  
//																		} 
																	

              
}




void Update_Euler_angles(_IMU *IMU,MPU_SENSOR *sen)
{
	
	  IMU->Pitch = (atan2(2*(IMU->q0*IMU->q1+IMU->q2*IMU->q3),1- 2*(IMU->q1*IMU->q1+IMU->q2*IMU->q2)) * 180.0f)/3.1415f;
    IMU->Roll = (asin(2*(IMU->q0*IMU->q2-IMU->q3*IMU->q1)) * 180.0f)/3.1415f ;
    IMU->Yaw = (atan2(2*(IMU->q0*IMU->q3+IMU->q1*IMU->q2),1- 2*(IMU->q2*IMU->q2+IMU->q3*IMU->q3)) * 180.0f)/3.1415f;  
    
    
    
    if(IMU->last_Yaw - IMU->Yaw < -320)
      IMU->Twokp_Y--;

    if(IMU->last_Yaw - IMU->Yaw > 320)
		  IMU->Twokp_Y++; 
          

		IMU->last_Yaw   = IMU->Yaw;
		
		
		IMU->Yaw = 360*IMU->Twokp_Y + IMU->Yaw;
		IMU->last_Roll  = IMU->Roll;
		IMU->last_Pitch = IMU->Pitch;
		
		
		Calculate_Static_Acc(IMU,sen);

		IMU->Earth_acc_z = 2*(IMU->q1 * IMU->q3 -IMU->q0 * IMU->q2) * sen->acc_x     +     2*(IMU->q2 * IMU->q3 + IMU->q0 * IMU->q1) * sen->acc_y     +     2*(IMU->q0 * IMU->q0 + IMU->q3 * IMU->q3 - 0.5f ) * sen->acc_z;    
		IMU->Earth_acc_z =((-sen->Gravity + IMU->Earth_acc_z)/sen->Gravity)*9.8f +0.07f ;
		
		if(fabs(IMU->Earth_acc_z) <0.02f)
			IMU->Earth_acc_z =0;
		
		IMU->Earth_acc_y = ((2*(IMU->q1 * IMU->q2 +IMU->q0 * IMU->q3) * sen->acc_x     +     2*(IMU->q0 * IMU->q0 + IMU->q2 * IMU->q2 - 0.5f ) * sen->acc_y     +    2*(IMU->q2 * IMU->q3 -IMU->q0 * IMU->q1) * sen->acc_z)/sen->Gravity)*9.8f;   
		IMU->Earth_acc_x = ((2*(IMU->q0 * IMU->q0 + IMU->q1 * IMU->q1 - 0.5f ) * sen->acc_x     +     2*(IMU->q1 * IMU->q2 -IMU->q0 * IMU->q3) * sen->acc_y     +    2*(IMU->q1 * IMU->q3 +IMU->q0 * IMU->q2) * sen->acc_z)/sen->Gravity)*9.8f; 

}


void Calculate_Static_Acc(_IMU *IMU,MPU_SENSOR *sen)
{
	float	tanRoll;
	
	float Roll,Pitch;
	
	Roll = IMU->Pitch;
	Pitch = IMU->Roll;
	
	tanRoll=tan(ToRad(Roll));
		
	IMU->pure_acc_x = -sen->Gravity*sin(ToRad(Pitch));
	IMU->pure_acc_z= sqrt (( (sen->Gravity*sen->Gravity) - (IMU->pure_acc_x*IMU->pure_acc_x) )/ ( (tanRoll*tanRoll) + 1 ) );
	IMU->pure_acc_y=sqrt( (sen->Gravity *sen->Gravity) - ( IMU->pure_acc_x*IMU->pure_acc_x) - ( IMU->pure_acc_z*IMU->pure_acc_z) );
	if(Roll<0)
			IMU->pure_acc_y= -IMU->pure_acc_y;

}





void MahonyAHRSupdateIMU123(_IMU *IMU,MPU_SENSOR *sen){//float gx, float gy, float gz, float ax, float ay, float az) {
	float recipNorm;
	float halfvx, halfvy, halfvz;
	float halfex, halfey, halfez;
	float qa, qb, qc;
	
	float q0=IMU->q0;
	float q1=IMU->q1;
	float q2=IMU->q2;
	float q3=IMU->q3;
	
	float gx = sen->gyro_x;
	float gy = sen->gyro_y;
	float gz = sen->gyro_z;
	
	float ax = sen->acc_x/sen->Gravity;
	float ay = sen->acc_y/sen->Gravity;
	float az = sen->acc_z/sen->Gravity;
	
	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {

		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;        

		// Estimated direction of gravity and vector perpendicular to magnetic flux
		halfvx = q1 * q3 - q0 * q2;
		halfvy = q0 * q1 + q2 * q3;
		halfvz = q0 * q0 - 0.5f + q3 * q3;
	
		// Error is sum of cross product between estimated and measured direction of gravity
		halfex = (ay * halfvz - az * halfvy);
		halfey = (az * halfvx - ax * halfvz);
		halfez = (ax * halfvy - ay * halfvx);

		// Compute and apply integral feedback if enabled
		if(Mahony_twoKiDef > 0.0f) {
			IMU->integralFBx += Mahony_twoKiDef * halfex * (1.0f / DT);	// integral error scaled by Ki
			IMU->integralFBy += Mahony_twoKiDef * halfey * (1.0f / DT);
			IMU->integralFBz += Mahony_twoKiDef * halfez * (1.0f / DT);
			gx += IMU->integralFBx;	// apply integral feedback
			gy += IMU->integralFBy;
			gz += IMU->integralFBz;
		}
		else {
			IMU->integralFBx = 0.0f;	// prevent integral windup
			IMU->integralFBy = 0.0f;
			IMU->integralFBz = 0.0f;
		}

		// Apply proportional feedback
		gx += Mahony_twoKpDef * halfex;
		gy += Mahony_twoKpDef * halfey;
		gz += Mahony_twoKpDef * halfez;
	}
	
	// Integrate rate of change of quaternion
	gx *= (0.5f * (1.0f / DT));		// pre-multiply common factors
	gy *= (0.5f * (1.0f / DT));
	gz *= (0.5f * (1.0f / DT));
	qa = q0;
	qb = q1;
	qc = q2;
	q0 += (-qb * gx - qc * gy - q3 * gz);
	q1 += (qa * gx + qc * gz - q3 * gy);
	q2 += (qa * gy - qb * gz + q3 * gx);
	q3 += (qa * gz + qb * gy - qc * gx); 
	// Normalise quaternion
	recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= recipNorm;
	q1 *= recipNorm;
	q2 *= recipNorm;
	q3 *= recipNorm;
	Mahony.q0=q0;
	Mahony.q1=q1;
	Mahony.q2=q2;
	Mahony.q3=q3;
}

void MahonyAHRSupdateIMU(_IMU *IMU,MPU_SENSOR *sen)
{
		float recipNorm;
		float halfvx, halfvy, halfvz;
		float halfex, halfey, halfez;
	
		float qa, qb, qc;
	
		float q0=IMU->q0;
		float q1=IMU->q1;
		float q2=IMU->q2;
		float q3=IMU->q3;
	
		float gx = sen->gyro_x;
		float gy = sen->gyro_y;
		float gz = sen->gyro_z;
	
		float ax = sen->acc_x/sen->Gravity;
		float ay = sen->acc_y/sen->Gravity;
		float az = sen->acc_z/sen->Gravity;
	
		
		if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) 
		{


						recipNorm = invSqrt(ax * ax + ay * ay + az * az);
						ax *= recipNorm;
						ay *= recipNorm;
						az *= recipNorm;        


						halfvx = q1 * q3 - q0 * q2;
						halfvy = q0 * q1 + q2 * q3;
						halfvz = q0 * q0 - 0.5f + q3 * q3;
		

						halfex = (ay * halfvz - az * halfvy);
						halfey = (az * halfvx - ax * halfvz);
						halfez = (ax * halfvy - ay * halfvx);


						if(Mahony_twoKiDef > 0.0f) {
										IMU->integralFBx += Mahony_twoKiDef * halfex * (DT);    
										IMU->integralFBy += Mahony_twoKiDef * halfey * (DT);
										IMU->integralFBz += Mahony_twoKiDef * halfez * (DT);
										gx += IMU->integralFBx;      
										gy += IMU->integralFBy;
										gz += IMU->integralFBz;
						}
						else {
										IMU->integralFBx = 0.0f;     
										IMU->integralFBy = 0.0f;
										IMU->integralFBz = 0.0f;
						}


						gx += IMU->Accel_weight * Mahony_twoKpDef * halfex;
						gy += IMU->Accel_weight * Mahony_twoKpDef * halfey;
						gz += IMU->Accel_weight * Mahony_twoKpDef * halfez;

		}
		

		gx *= (0.5f * DT);             
		gy *= (0.5f * DT);
		gz *= (0.5f * DT);
		qa = q0;
		qb = q1;
		qc = q2;
		q0 += (-qb * gx - qc * gy - q3 * gz);
		q1 += (qa * gx + qc * gz - q3 * gy);
		q2 += (qa * gy - qb * gz + q3 * gx);
		q3 += (qa * gz + qb * gy - qc * gx); 
		

		recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
		q0 *= recipNorm;
		q1 *= recipNorm;
		q2 *= recipNorm;
		q3 *= recipNorm;
		
		
		IMU->q0 = q0;
		IMU->q1 = q1;
		IMU->q2 = q2;
		IMU->q3 = q3;
  }








// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root

float invSqrt(float x) 
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}
