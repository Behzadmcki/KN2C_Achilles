#ifndef __Bus_HPP__
#define __Bus_HPP__

#include "main.h"
#include "stm32f4xx_hal.h"
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
	int packetSize  ;
	
	
	HeaderPacket () 
	{
		
	}
	HeaderPacket ( char _firstByte, char _secondByte, char _thirdByte, char _packetID, char _packetSize )
	{
		firstByte = _firstByte ;
		secondByte = _secondByte ;
		thirdByte = _thirdByte ;
	  packetID = _packetID ;
	  packetSize = _packetSize ;
	}
};



class BUS
{
	private:
		
	public:
		
		BUS() ;
		vector <char> driver_buff ;
	  vector <char> address_buff ;
	
	  void HipHop (void);	
	  void CheckHeader (struct HeaderPacket* HeaderPacket);
	  void Fillbuffer (struct HeaderPacket* HeaderPacket);
	  void CheckEnd (struct HeaderPacket* HeaderPacket ); 
    void VectorCheck (void);
	  void ReadAD (void );
	  void GetPacket();
	  void static BusInit();
		
};


#endif



