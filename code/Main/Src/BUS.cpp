#include "BUS.hpp" 
#include "variable.h"



	
BUS::BUS() 
{ }


void BUS::BusInit(void)
{
	busStatus = ready;
  bus.HipHop ();
	bus.main_buff.resize(PWM_pkg.pkgSize );  //CHANGED

	HAL_UART_Receive_DMA(&huart3,&recHeader,1);
	HAL_UART_Receive_DMA(&huart1,&recHeader,1);
}
void BUS::HipHop (void)
{
	for (int counter=0;counter<6;counter ++)
	{
	  Toggle_LED_blue ;
  	Toggle_LED_red;
		HAL_Delay(100);
	}
}
void BUS::GetPacket (void)
{
				switch( recStatus ) 
				{
					case ReceiveHeader:
					   
						 CheckHeader( &PWM_pkg );
						 break;
					case ReceiveData:
						
						Fillbuffer ( &PWM_pkg );
						break;
				};

  
}
void BUS::CheckHeader (struct HeaderPacket* HeaderPacket)
{
	switch (HeaderPacket->headerCounter)
	{
		case 0:
			if ( recHeader == 'P'  )
			{				
				HeaderPacket->headerCounter++;  
			}
			else          										             HeaderPacket->headerCounter=0;
		  break; 
		case 1:
		  if ( recHeader == 'W' )  
			{				
				HeaderPacket->headerCounter++; 

			}
			else if(recHeader == 'P')  HeaderPacket->headerCounter=1;
			else                                           HeaderPacket->headerCounter=0;
			break; 
		case 2:
			if ( recHeader == 'M'  )   // tayid header
      { 
				packetSize = HeaderPacket->pkgSize   ;
				recStatus  = ReceiveData ;
  			headerMode=HeaderPacket->packetID;  
				HeaderPacket->headerCounter=0 ;	
			
			}   	
	    break; 
	}	
}
void BUS::Fillbuffer ( struct HeaderPacket* HeaderPacket)
{

	if (headerMode == PWMMode  )
	{
		
		for (fillCounter= 3;fillCounter<packetSize  ;fillCounter++ )
		{
	     main_buff.at(fillCounter ) = recData[fillCounter - 3] ;
		}
					sendBuffer_test1 = main_buff.at(3);
					sendBuffer_test2 = main_buff.at(4);
					sendBuffer_test3 = main_buff.at(5);
					sendBuffer_test4 = main_buff.at(6);
		      sendBuffer_test5 = main_buff.at(7);
					sendBuffer_test6 = main_buff.at(8);
					sendBuffer_test7 = main_buff.at(9);
		      sendBuffer_test8 = main_buff.at(10);
					sendBuffer_test9 = main_buff.at(11);
					sendBuffer_test10 = main_buff.at(12);
					sendBuffer_test11 = main_buff.at(13);
					sendBuffer_test12 = main_buff.at(14);
					
		
	}


	
//		for (int counter=0;counter<35;counter++)
//			 recData[counter] = 0;
		CheckEnd(HeaderPacket) ;
}


void BUS::CheckEnd (struct HeaderPacket* HeaderPacket )
{
											
	recieveCheckSum = 0;
	 if (headerMode == PWMMode  )
  { 
 	
		 for (int counter=3;counter<packetSize  -2;counter++ )
	   {
				recieveCheckSum += main_buff.at(counter);
				recieveCheckSum = recieveCheckSum %256;	
	   }
  	if (/* recieveCheckSum  == main_buff.at( packetSize -2 ) &&*/ '\r' == main_buff.at( packetSize  -1 ) )  
	  {	
			
			busStatus = busy;
			HAL_TIM_Base_Start_IT(&htim4);
			Toggle_LED_blue ;
			
      mainOrder = ready;
			headerOrder = headerMode  ;
	   	
	  }
	}

	recStatus = ReceiveHeader ;
	
  
}
void BUS::SendPacket (int driverAD,int DATA1, int DATA2, int DATA3,int DATA4, int DATA5,int DATA6,int DATA7,int DATA8)
{
	
	for(int counter=0;counter<15;counter++)
	   sendBuffer[counter]= NULL;
					sendBuffer[0] = 'P';
					sendBuffer[1] = 'W';
					sendBuffer[2] = 'M';
					sendBuffer[3] = driverAD;
		      sendBuffer[4] = 15;
					sendBuffer[5] = DATA1;
					sendBuffer[6] = DATA2;
		      sendBuffer[7] = DATA3;
					sendBuffer[8] = DATA4;
					sendBuffer[9] = DATA5;
					sendBuffer[10] = DATA6;
					sendBuffer[11] = DATA7;
					sendBuffer[12] = DATA8;
	
	        
		
		      sendCheckSum= 0;
					for(int counter =3;counter<15 - 2;counter++)  
					{
						sendCheckSum += sendBuffer [counter];
						sendCheckSum  = sendCheckSum % 256;
					}
					sendBuffer[13] = sendCheckSum  ;
					sendBuffer[14] = '\r' ;
					EN_ADM_Set ;
					sendDriverStatus = busy;
					HAL_UART_Transmit_DMA(&huart1 , sendBuffer   ,15);									
}



//void BUS::SendPacketHead (struct HeaderPacket* HeaderPacket , int driverAD,int DATA1, int DATA2, int DATA3,int DATA4, int DATA5,int DATA6,int DATA7,int DATA8 )
//{
//					sendBufferHead[0] = HeaderPacket ->firstByte;
//					sendBufferHead[1] = HeaderPacket ->secondByte;
//					sendBufferHead[2] = HeaderPacket ->thirdByte ;
//					sendBufferHead[3] = driverAD;
//		      sendBufferHead[4] = DATA1;
//					sendBufferHead[5] = DATA2;
//					sendBufferHead[6] = DATA3;
//		      sendBufferHead[7] = DATA4;
//		      sendBufferHead[8] = DATA5;
//	      	sendBufferHead[9] = DATA6;
//					sendBufferHead[10] = DATA7;
//					sendBufferHead[11] = DATA8;

//					
//					sendCheckSum= 0;
//					for(int counter =3;counter<HED_pkg.pkgSize  - 2;counter++)   
//					{
//						sendCheckSum += sendBufferHead [counter];
//						sendCheckSum  = sendCheckSum % 256;
//					}
//					
//					sendBufferHead[12] = sendCheckSum  ;
//					sendBufferHead[13] = '\r' ;
//					EN_ADM_Set ;
//					sendDriverStatus = busy;
//					HAL_UART_Transmit_DMA(&huart1 , sendBufferHead    ,14);	
//}


void BUS::SendPkgPWM()
{

	switch(sendOrder)
	{
		case 0:   //slave 1

			SendPacket (Slave1_AD, main_buff.at(3),main_buff.at(4),main_buff.at(5),main_buff.at(6),main_buff.at(7),main_buff.at(8),NULL,NULL);
			break;
	  case 1:   //slave 2
			
			SendPacket (Slave2_AD , main_buff.at(9),main_buff.at(10),main_buff.at(11),main_buff.at(12),main_buff.at(13),main_buff.at(14),NULL,NULL);
			
		  mainOrder = busy;
//		  Toggle_LED_red ;
		break;
			
	};
	
}




void BUS::UsartReceive( UART_HandleTypeDef *usartType,int dataLenght)
{
			if (recStatus==ReceiveData )
			{
				 HAL_UART_Receive_DMA(usartType,recData ,dataLenght-3);
			}
			else if(recStatus == ReceiveHeader )
			{
				
	  			HAL_UART_Receive_DMA(usartType,&recHeader,1);
			}
}




