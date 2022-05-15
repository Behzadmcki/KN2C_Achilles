#ifndef VarS
#define VarS
#include "define.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include "tim.h"
#include "gpio.h"
#include "usart.h"
#include "mpu6050.h"
#include "IMU.h"

extern char receive1 , UART_bufferfbus[100] , Head_data[5];
extern int resolution;





			

			
			
			/****************************************    IMU   **********************************************/		


extern int status_i2c;
extern char ping;
extern char receive2;
//extern MPU_SENSOR Mpu;
//extern _IMU Mahony;

			/*************************************uart*********************************************/
extern unsigned char AX_Pitch_pose;
extern unsigned char AX_KinectYaw_pose;
extern unsigned char RX_pose;
extern char servo_pos;
extern uint8_t uart_tx_bus_buffer[28];
typedef union {float f; unsigned char c[sizeof(float)];} data_packet;
extern data_packet send[6];
extern unsigned char tempp[4];
//extern unsigned char teemp;
extern float fdeg;
extern int ideg;
//filter
extern float filter_roll;
extern float last_roll;
extern float filter_pitch;
extern float last_pitch;
#endif
