#ifndef __Bus_HPP__
#define __Bus_HPP__

#include "main.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "tim.h"
#include <vector>

using namespace std ;

struct HeaderPacket 
{
	char firstByte ;
	char secondByte ;
	char thirdByte ;
	char packetID;
	char headerCounter ;
	int pkgSize  ;	
	HeaderPacket ()  { }  
	HeaderPacket ( char _firstByte, char _secondByte, char _thirdByte, char _packetID, char _pkgSize )
	{
		firstByte = _firstByte ;
		secondByte = _secondByte ;
		thirdByte = _thirdByte ;
	  packetID = _packetID ;
	  pkgSize = _pkgSize ;
	}
};
class BUS
{
	public:	
		BUS();

		vector <char> main_buff;
	  void HipHop (void);	
	  void CheckHeader (struct HeaderPacket* HeaderPacket);
	  void Fillbuffer ( struct HeaderPacket* HeaderPacket);
	  void CheckEnd ( struct HeaderPacket* HeaderPacket ); 
	  void SendPacket (int driverAD,int DATA1, int DATA2, int DATA3,int DATA4, int DATA5,int DATA6,int DATA7,int DATA8 );
		void SendPkgPWM(void);
		void GetPacket(void);
		void UsartReceive(UART_HandleTypeDef *usartType,int dataLenght);
		void static BusInit(void);
};


#endif



