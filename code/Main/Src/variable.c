#include "stm32f1xx_hal.h"
#include "Bus.hpp"
#include <variable.h>


BUS bus;


HeaderPacket  PWM_pkg('P', 'W', 'M', 1, 40);
HeaderPacket  HED_pkg('H', 'E', 'D', 4, 14);
int sendBuffer_test1;
int sendBuffer_test2;
int sendBuffer_test3;
int sendBuffer_test4;
int sendBuffer_test5;
int sendBuffer_test6;
int sendBuffer_test7;
int sendBuffer_test8;
int sendBuffer_test9;
int sendBuffer_test10;
int sendBuffer_test11;
int sendBuffer_test12;
int sendBuffer_test13;
int sendBuffer_test14;
int sendBuffer_test15;
int sendBuffer_test16;

int test = 0;
int headerCounter = 0;
int mainCounter = 0;
int fillCounter = 3; 
int packageState = 0;
uint8_t recHeader;
uint8_t recData[37];
uint8_t sendBuffer[15] = {} ;
uint8_t sendBufferHead[14] = {} ;	
int headerMode=0;
int counter = 0;
int driverAD = 0;
int sendOrder = 0;
int bufferCounter = 0;
int sendCheckSum = 0;
int recieveCheckSum = 0;
int recStatus = 0;
int nrfStatus = 0;
UART_HandleTypeDef *usartType;
int dataLenght=0;
int packetSize = 0;
int busStatus=0;
	

int mainOrder = 0;
int headerOrder=0;
int sendDriverStatus=0;