#include "BUS.hpp"
#include "variable.h"
#include "gpio.h"
BUS::BUS()
{

}

void BUS::BusInit()
{
 EN_ADM_Reset ;
recStatus=ReceiveHeader ;
 HAL_UART_Receive_DMA(&huart2,&recHeader,1) ;
}

void BUS::HipHop (void)
{
	for (int counter=0;counter<6;counter ++)
	{
	  Toggle_LED_blue;
  	Toggle_LED_red;
		HAL_Delay(100);
	}
}
void BUS::GetPacket()
{
	
	
			switch( recStatus ) 
			{
				case ReceiveHeader:
				{

					 CheckHeader( &HED_pkg  );
					 CheckHeader( &FDB_pkg );
					 
					 break;
				}
				case ReceiveData:
				{
					if (headerMode == HEDMode  )
					{
            Fillbuffer ( &HED_pkg  );
					}						
					else if (headerMode == FDBMode  )
					{
						Fillbuffer ( &FDB_pkg  );
					}
					
					break;
				}
			};	
}
void BUS::CheckHeader (struct HeaderPacket* HeaderPacket)
{
	
	switch (HeaderPacket->headerCounter)
	{
		case 0:
		{
			
			if ( recHeader == HeaderPacket->firstByte  )  { HeaderPacket->headerCounter++;    }
			else          										       HeaderPacket->headerCounter=0;
		  break; 
		}
		case 1:
		{
			
		  if ( recHeader == HeaderPacket->secondByte )  { HeaderPacket->headerCounter++; }
			else if(recHeader == HeaderPacket->firstByte)  HeaderPacket->headerCounter=1;
			else                                     HeaderPacket->headerCounter=0;
			break; 
		}
		case 2:
		{
		
			if ( recHeader == HeaderPacket->thirdByte )   
			{						
				if(HeaderPacket->firstByte == FDB_pkg.firstByte)
				{
					HeaderPacket->headerCounter++;
					
				}
				else
				{
					
					headerSize=3;
					packetSize = HED_pkg.packetSize ;
					recStatus = ReceiveData ;
					headerMode=HeaderPacket->packetID; 
					HeaderPacket->headerCounter=0 ; 			
				}
			}
      else
				{
					HeaderPacket->headerCounter = 0 ;
					recStatus = ReceiveHeader ;
				}
	    break; 
		}
		case 3:
		{
			if(HeaderPacket->firstByte == FDB_pkg.firstByte)
			{
				

				if(recHeader == NULL)
				{
					HeaderPacket->headerCounter = 0 ;
					recStatus = ReceiveData ;
					headerSize = 4 ;
					packetSize = 15 ;
					headerMode = HeaderPacket->packetID ;
				}
				else
				{
					HeaderPacket->headerCounter = 0 ;
					recStatus = ReceiveHeader ;
				}
			}
			break;
		}
		
	}		
}
void BUS::Fillbuffer ( struct HeaderPacket* HeaderPacket)
{ 

		recStatus = ReceiveHeader;
	if(headerMode == FDBMode )
	{
				address_buff.resize (11);

				for (fillCounter=0;fillCounter<HeaderPacket->packetSize - 4;fillCounter++)
					address_buff.at(fillCounter )= recData [fillCounter];
				recieveCheckSum = 0;
				for (int i=0 ; i<HeaderPacket->packetSize -6;i++)
				{
					 recieveCheckSum += address_buff.at(i);
					 recieveCheckSum = recieveCheckSum %256;

				}
	}
	else
	{
		
		
					driver_buff.resize (HeaderPacket->packetSize   );
					driver_buff.at(0) = HeaderPacket->firstByte ;
					driver_buff.at(1) = HeaderPacket->secondByte ;
					driver_buff.at(2) = HeaderPacket->thirdByte ;
					for (fillCounter=3;fillCounter<HeaderPacket->packetSize ;fillCounter++)
						driver_buff.at(fillCounter )= recData [fillCounter - 3];
					
					recieveCheckSum = 0;
					for (int i=3 ; i<HeaderPacket->packetSize -2;i++)
					{
						 recieveCheckSum += driver_buff.at(i);
						 recieveCheckSum = recieveCheckSum %256;

					}
					
  } 
	CheckEnd ( HeaderPacket );

  VectorCheck (); 
	
	
}
void BUS::VectorCheck ( void  )
{
	for ( int i=0; i< 12 ; i++)
		vectorCheck[i] = recData[i];
}
void BUS::CheckEnd (struct HeaderPacket* HeaderPacket )
{
	if(headerMode == FDBMode )
	{
			if (recieveCheckSum == address_buff.at(9 ) &&  '\r' == address_buff.at( 10 ) )  
			{	
				
				// packet valid
					CheckAddress();

			}
  }
	else 
	{
		  if (recieveCheckSum == driver_buff.at( HeaderPacket->packetSize -2 ) &&  '\r' == driver_buff.at( HeaderPacket->packetSize -1 ) )  
			{
				// packet valid

				Toggle_LED_blue;
				global_validation=1; 
				Global_Connection_CNT=0;
        
				
			}
	}
	
				
	
}

void BUS::CheckAddress (void)
{
	for(int counter=0;counter<10;counter++)
	  if(address_buff.at(counter)== globalDriverAD )
		{
			HAL_TIM_Base_Start_IT(&htim3);
			TIM3->CNT=(counter+1)*40;
			
		}
	
	
}


void BUS::FeedBack(void) 
{

	sendBuffer[0]='F';
	sendBuffer[1]='D';
	sendBuffer[2]='B';
	sendBuffer[3]=globalDriverAD   ;
	sendBuffer[4]=Data_gas;
	sendCheckSum  = 0;
	for (int i=3 ; i<20-2;i++)
	{
		 sendCheckSum += sendBuffer [i];
		 sendCheckSum = sendCheckSum %256;
	}
  sendBuffer[18]=sendCheckSum;
	sendBuffer[19]='\r';
}


