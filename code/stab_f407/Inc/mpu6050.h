#ifndef H_Mpu605_H
#define H_Mpu605_H

#include "stm32f4xx_hal.h"
//#include "Define.h"
#include "main.h"
#include "math.h"
//#include "EEPROM.h"

// gyro ro int kardam moshkel khord avaz kon

#define 		DT																	0.025f
#define 		Time																DT*10000.0f
// MPU 6000 registers
#define     MPUREG_WHOAMI                       0x75 
#define     MPUREG_SMPLRT_DIV                   0x19 
#define     MPUREG_CONFIG                       0x1A 
#define     MPUREG_GYRO_CONFIG                  0x1B
#define     MPUREG_ACCEL_CONFIG                 0x1C
#define     MPUREG_INT_PIN_CFG                  0x37
#define     MPUREG_INT_ENABLE                   0x38 
#define     MPUREG_ACCEL_XOUT_H                 0x3B 
#define     MPUREG_ACCEL_XOUT_L                 0x3C 
#define     MPUREG_ACCEL_YOUT_H                 0x3D 
#define     MPUREG_ACCEL_YOUT_L                 0x3E 
#define     MPUREG_ACCEL_ZOUT_H                 0x3F 
#define     MPUREG_ACCEL_ZOUT_L                 0x40 
#define     MPUREG_TEMP_OUT_H                   0x41
#define     MPUREG_TEMP_OUT_L                   0x42
#define     MPUREG_GYRO_XOUT_H                  0x43 
#define     MPUREG_GYRO_XOUT_L                  0x44
#define     MPUREG_GYRO_YOUT_H                  0x45
#define     MPUREG_GYRO_YOUT_L                  0x46
#define     MPUREG_GYRO_ZOUT_H                  0x47
#define     MPUREG_GYRO_ZOUT_L                  0x48
#define     MPUREG_USER_CTRL                    0x6A
#define     MPUREG_PWR_MGMT_1                   0x6B
#define     MPUREG_PWR_MGMT_2                   0x6C

// Configuration bits  MPU 6000

#define     BIT_SLEEP                  				 0x40
#define     BIT_H_RESET                 			 0x80
#define     BITS_CLKSEL                 			 0x07
#define     MPU_CLK_SEL_PLLGYROX        			 0x01
#define     MPU_CLK_SEL_PLLGYROZ        			 0x03
#define     MPU_EXT_SYNC_GYROX          			 0x02
#define     BITS_FS_250DPS              			 0x00
#define     BITS_FS_500DPS              			 0x08
#define     BITS_FS_1000DPS             			 0x10
#define     BITS_FS_2000DPS             	 		 0x18
#define     BITS_FS_MASK               	  		 0x18
#define     BITS_DLPF_CFG_256HZ_NOLPF2         0x00
#define     BITS_DLPF_CFG_188HZ          			 0x01
#define     BITS_DLPF_CFG_98HZ        			   0x02
#define     BITS_DLPF_CFG_42HZ       				   0x03
#define     BITS_DLPF_CFG_20HZ        			   0x04
#define     BITS_DLPF_CFG_10HZ        			   0x05
#define     BITS_DLPF_CFG_5HZ         			   0x06
#define     BITS_DLPF_CFG_2100HZ_NOLPF      	 0x07
#define     BITS_DLPF_CFG_MASK        			   0x07
#define     BIT_INT_ANYRD_2CLEAR       				 0x10
#define     BIT_RAW_RDY_EN             				 0x01
#define     BIT_I2C_IF_DIS            			 	 0x10




// MPU6000 sensibility  (theorical 0.0152 => 1/65.6LSB/deg/s at 500deg/s) (theorical 0.0305 => 1/32.8LSB/deg/s at 1000deg/s) ( 0.06098 => 1/16.4LSB/deg/s at 2000deg/s)
#define Gyro_Gain_X         0.06098f  
#define Gyro_Gain_Y         0.06098f
#define Gyro_Gain_Z         0.06098f   

#define ToRad(x)            (x*0.01745329252f)  // *pi/180
#define ToDeg(x)            (x*57.2957795131f)  // *180/pi


#define Gyro_Scaled_X(x)    x*ToRad(Gyro_Gain_X) //Return the scaled ADC raw data of the gyro in radians for second
#define Gyro_Scaled_Y(x)    x*ToRad(Gyro_Gain_Y) //Return the scaled ADC raw data of the gyro in radians for second
#define Gyro_Scaled_Z(x)    x*ToRad(Gyro_Gain_Z) //Return the scaled ADC raw data of the gyro in radians for second


// filter
#define GyroThreshold           30
#define	PI				    3.1415926535f

#define F_CUT_GRAVITY_hpf       4
#define F_CUT_GRAVITY_lpf       10
#define	F_CUT_G_PRINT 			    100
#define	F_CUT_ACC			   			  8 
#define F_CUT_CAM_DIFF					10


#define FILTER_G_PRINT          1/(2*PI*F_CUT_G_PRINT		      	)
#define FILTER_GRAVITY_hpf      1/(2*PI*F_CUT_GRAVITY_hpf     	)
#define FILTER_GRAVITY_lpf      1/(2*PI*F_CUT_GRAVITY_lpf     	)
#define FILTER_ACC              1/(2*PI*F_CUT_ACC			        	) 
#define FILTER_CAM_DIFF         1/(2*PI*F_CUT_CAM_DIFF	      	)




//****************************************************************
 typedef struct {
	 
	 char Add;
	 
	 float acc_x,acc_y,acc_z;
	 float last_acc_x,last_acc_y,last_acc_z;
	 
	 float gyro_x,gyro_y,gyro_z;
	 float gyro_x_real,gyro_y_real,gyro_z_real;
	 float gyrox_offset,gyroy_offset,gyroz_offset;
	 
	 float Gravity;
	 
	 float Accel_magnitude,last_Accel_magnitude,Accel_magnitude_hpf,last_Accel_magnitude_hpf;
	 float g_print,last_g_print;
	 
	 I2C_HandleTypeDef I2C;	 
	 
}MPU_SENSOR;
 

//typedef struct _MPU_SENSOR MPU_SENSOR;

union _ch2int 
{
    int16_t real;
    char byte[2];
};

typedef union _ch2int  ch2int;

 


extern MPU_SENSOR Mpu;
extern MPU_SENSOR Mpu_ODO;
extern ch2int _con;

//****************************************************************
void init_mpu(MPU_SENSOR *sen,I2C_HandleTypeDef *hi2cx , int address , int calib);

void Mpu_Write(MPU_SENSOR *sen,char Reg,char data);
void Mpu_Read_acc(MPU_SENSOR *sen);
void Mpu_Read_gyro(MPU_SENSOR *sen);
void gyro_calib(MPU_SENSOR *sen,char permision);
void Mpu_update(MPU_SENSOR *sen);


void Update_Gravity(MPU_SENSOR *sen);
char ping_mpu(MPU_SENSOR *sen);
char Mpu_Read(MPU_SENSOR *sen,char Reg);

#endif 

