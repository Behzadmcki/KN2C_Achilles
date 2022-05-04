#include "stm32f4xx_hal.h"
#include "variable.h"
 
BUS bus;


HeaderPacket  PWM_pkg('P', 'W', 'M',1 ,15 );



int vectorCheck[35]={};
int vectorCheck1=0;
int vectorCheck2=0;
int vectorCheck3=0;
int vectorCheck4=0;
int vectorCheck5=0;
int vectorCheck6=0;
int vectorCheck7=0;
int vectorCheck8=0;
int vectorCheck9=0;
int vectorCheck10=0;
int vectorCheck11=0;
int vectorCheck12=0;
int vectorCheck13=0;
int vectorCheck14=0;
int vectorCheck15=0;
int	dastan=0;

int headerCounter=0;
int fillCounter=4; 
uint8_t recHeader;
uint8_t recData[12];
uint8_t sendBuffer[20] ; 
int headerMode=0;
int globalDriverAD  =0;
int recieveCheckSum = 0;
int recStatus = 0;
int packetSize=0;
int headerSize=0;
int settingType=0;

	
	// MOTOR
int	checkConnection=0;
int motorInv[4][3]={0};
int motorTimer =0;

	
	


