#include <Global_variable.h>


/*************************************************  IMU   *************************************/
int status_i2c;
char ping;
char receive2;
//MPU_SENSOR Mpu;
//_IMU Mahony;
volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;
/*****************************uart******************************/
char receive1 , UART_bufferfbus[100] , Head_data[5];
unsigned char AX_Pitch_pose=150;
unsigned char AX_KinectYaw_pose=150;
unsigned char RX_pose=150;

char servo_pos=0;

uint8_t uart_tx_bus_buffer[28];


data_packet send[6];

unsigned char tempp[4];
//unsigned char teemp;
float fdeg;
int ideg;
/////filter
float filter_roll=0;
float last_roll=0;
float filter_pitch=0;
float last_pitch=0;