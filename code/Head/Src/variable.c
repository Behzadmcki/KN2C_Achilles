#include "variable.h"
 
BUS bus;


HeaderPacket  HED_pkg('H', 'E', 'D',4 ,14 );
HeaderPacket  FDB_pkg('F', 'D', 'B',3 ,15);
            

int test= 0 ;
int test2= 0 ;
int test3=0 ;
int dastan=0;
int vectorCheck[35]={};
int headerCounter=0;
int fillCounter=4; 
uint8_t recHeader;
uint8_t recData[12];
uint8_t sendBuffer[20] ; 
int headerMode=0;
int timer= 0;
int recieveCheckSum = 0;
int sendCheckSum = 0;
int recStatus = 0;
int packetSize=0;
int headerSize=0;
uint16_t adcValue[3]={};
int firstIRQ=0;
int firstCheckConnection=0;
int Head_Command[8]={};
int Data_gas=0;
int Global_Connection_CNT=0 ;
int global_validation=0;
int	SendStatus=0 ;

	
	
	
	
	


