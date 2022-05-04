#ifndef __IMU_HPP__
#define __IMU_HPP__

#include "main.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "tim.h"
#include <vector>
#include "math.h"


using namespace std ;

struct HeaderPacketImu
{
	char firstByteImu;
	char secondByteImu ;
	
	char packetIDImu;
	char headerCounterImu ;
	int packetSizeImu  ;
	
	
	HeaderPacketImu () 
	{
		
	}
	HeaderPacketImu ( char _firstByte, char _secondByte,char _packetID, char _packetSize )
	{
		firstByteImu = _firstByte ;
		secondByteImu = _secondByte ;
	  packetIDImu = _packetID ;
	  packetSizeImu= _packetSize ;
	}
};

//struct ImuParamData
//	
//{
//			
//	   

//	
//			ImuParamData ()
//			{
//				
//			}
//			ImuParamData(int _imuId)
//			{
//			imuId=_imuId;	
//			}
//};
	

class IMU
{
	private:
		
	public:
		IMU() ;
		IMU(int _imuId) ;
	
		int   imuId;
		double imuAx;
		double imuAY;
		double imuAZ;
		double imuWx;
		double imuWy;
		double imuWz;
		double imuRoll;
		double imuPitch;
		double imuYaw;	
	
		
		double filteredWx;
		double filteredWy;
		double filteredWz;


		double lastWx;
		double lastWy;
		double lastWz;
		
		float offsetWx;
	  float offsetWy;
		float offsetWz;

	  vector <char> Imu_buff;
	  void CheckHeaderImu (struct HeaderPacketImu* HeaderPacketImu);
	  void FillbufferImu (void);
	  void CheckEndImu (void); 
	  void GetPacketImu();
	  void static IMUInit();
		void static MakeparamImu (void);
	  void CalculateImu(void);
	  void static ChooseImu ();
	  void GetImuOffset();
};


#endif

