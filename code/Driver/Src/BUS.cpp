#include "BUS.hpp"
#include <variable.h>
#include "gpio.h"
BUS::BUS()
{

}

void BUS::BusInit()
{
 bus.HipHop();
 bus.ReadAD ();
 EN_ADM_Reset ;
 recStatus=ReceiveHeader ;
}
void BUS::ReadAD (void )
{

	globalDriverAD = 0x20 + 2	;
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
					
					 bus.CheckHeader( &PWM_pkg );				 
					 break;
				}
				case ReceiveData:
				{
						bus.Fillbuffer ( &PWM_pkg );
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
			
			if ( recHeader == 'P'  )   HeaderPacket->headerCounter++;   
			else          										       			 HeaderPacket->headerCounter=0;
		  break; 
		}
		case 1:
		{
			
		  if ( recHeader == 'W' )   HeaderPacket->headerCounter++; 
			else if(recHeader == 'P')  HeaderPacket->headerCounter=1;
			else                                    			 HeaderPacket->headerCounter=0;
			break; 
		}
		case 2:
		{
			if ( recHeader == 'M' )    
			{
									HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);	

				HeaderPacket->headerCounter++;
			}
      else if(recHeader == 'P')  HeaderPacket->headerCounter=1;
			else                                    			 HeaderPacket->headerCounter=0;
	    break; 
		}
		case 3:
		{
			if(recHeader == globalDriverAD)
			{
				HeaderPacket->headerCounter ++ ;
			}
			else 
				HeaderPacket->headerCounter = 0 ;
			break;
		}
		case 4:
		{
			  headerSize=HeaderPacket->headerCounter + 1 ;
			  packetSize = recHeader;
			  recStatus = ReceiveData ;
				headerMode=HeaderPacket->packetID; 
        HeaderPacket->headerCounter=0 ; 			
			  break;
		}
	}		
}
void BUS::Fillbuffer ( struct HeaderPacket* HeaderPacket)
{ 
	
		
	driver_buff.resize (HeaderPacket->packetSize   );
	driver_buff.at(0) = 'P' ;
	driver_buff.at(1) = 'W' ;
	driver_buff.at(2) = 'M' ;
	driver_buff.at(3) = globalDriverAD ;
	driver_buff.at(4) = packetSize ;
	for (fillCounter=5;fillCounter<HeaderPacket->packetSize ;fillCounter++)
		driver_buff.at(fillCounter )= recData [fillCounter - 5];
	
	recieveCheckSum = 0;
	for (int i=3 ; i<HeaderPacket->packetSize -2;i++)
	{
		 recieveCheckSum += driver_buff.at(i);
		 recieveCheckSum = recieveCheckSum %256;

	}
					
	CheckEnd ( HeaderPacket );
  VectorCheck (); 
	
	
}
void BUS::VectorCheck ( void  )
{
	for ( int i=0; i< 15 ; i++)
	{
		vectorCheck[i] = driver_buff.at(i);
	}
		vectorCheck1 = driver_buff.at(0);
		vectorCheck2 = driver_buff.at(1);
	  vectorCheck3 = driver_buff.at(2);
	  vectorCheck4 = driver_buff.at(3);
	  vectorCheck5 = driver_buff.at(4);
	  vectorCheck6 = driver_buff.at(5);
	  vectorCheck7 = driver_buff.at(6);
	  vectorCheck8 = driver_buff.at(7);
	  vectorCheck9 = driver_buff.at(8);
	  vectorCheck10 = driver_buff.at(9);
	  vectorCheck11 = driver_buff.at(10);
	  vectorCheck12 = driver_buff.at(11);	
	  vectorCheck13 = driver_buff.at(12);
	  vectorCheck14 = driver_buff.at(13);
	  vectorCheck15 = driver_buff.at(14);	
	
}
void BUS::CheckEnd (struct HeaderPacket* HeaderPacket )
{

	{
		  if (recieveCheckSum == driver_buff.at( HeaderPacket->packetSize -2 ) &&  '\r' == driver_buff.at( HeaderPacket->packetSize -1 ) )  
			{
				// packet valid
 
				Toggle_LED_blue;
				Toggle_LED_red;
				checkConnection = 0;
//				motor1.motorMode = headerMode ;
//				motor2.motorMode = headerMode ;
//				motor3.motorMode = headerMode ;
				dastan=1;
				
//				if(driver_buff.at(5)== Forward_Mode)
//				{
//					HAL_GPIO_WritePin(INA_1_GPIO_Port,INA_1_Pin,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(INB_1_GPIO_Port,INB_1_Pin,GPIO_PIN_RESET);
//					__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, driver_buff.at(6)*9.6) ;
//				}
//				else if(driver_buff.at(5)==Reverse_Mode)
//				{
//					HAL_GPIO_WritePin(INA_1_GPIO_Port,INA_1_Pin,GPIO_PIN_RESET);
//		      HAL_GPIO_WritePin(INB_1_GPIO_Port,INB_1_Pin,GPIO_PIN_SET);
//					__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, driver_buff.at(6)*9.6) ;
//				}
//				else
//				{
//					HAL_GPIO_WritePin(INA_1_GPIO_Port,INA_1_Pin,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(INB_1_GPIO_Port,INB_1_Pin,GPIO_PIN_SET);
//					__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, driver_buff.at(6)*9.6) ;
//				}
//				
//				
//				if(driver_buff.at(7)== Forward_Mode)
//				{
//					HAL_GPIO_WritePin(INA_2_GPIO_Port,INA_2_Pin,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(INB_2_GPIO_Port,INB_2_Pin,GPIO_PIN_RESET);
//					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, driver_buff.at(8)*9.6) ;
//				}
//				else if(driver_buff.at(7)==Reverse_Mode)
//				{
//					HAL_GPIO_WritePin(INA_2_GPIO_Port,INA_2_Pin,GPIO_PIN_RESET);
//		      HAL_GPIO_WritePin(INB_2_GPIO_Port,INB_2_Pin,GPIO_PIN_SET);
//					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, driver_buff.at(8)*9.6) ;
//				}
//				else
//				{
//					HAL_GPIO_WritePin(INA_2_GPIO_Port,INA_2_Pin,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(INB_2_GPIO_Port,INB_2_Pin,GPIO_PIN_SET);
//					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, driver_buff.at(8)*9.6) ;
//				}
//				
//				if(driver_buff.at(9)== Forward_Mode)
//				{
//					HAL_GPIO_WritePin(INA_3_GPIO_Port,INA_3_Pin,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(INB_3_GPIO_Port,INB_3_Pin,GPIO_PIN_RESET);
//					__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, driver_buff.at(10)*9.6) ;
//				}
//				else if(driver_buff.at(9)==Reverse_Mode)
//				{
//					HAL_GPIO_WritePin(INA_3_GPIO_Port,INA_3_Pin,GPIO_PIN_RESET);
//		      HAL_GPIO_WritePin(INB_3_GPIO_Port,INB_3_Pin,GPIO_PIN_SET);
//					__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, driver_buff.at(10)*9.6) ;
//				}
//				else
//				{
//					HAL_GPIO_WritePin(INA_3_GPIO_Port,INA_3_Pin,GPIO_PIN_SET);
//					HAL_GPIO_WritePin(INB_3_GPIO_Port,INB_3_Pin,GPIO_PIN_SET);
//					__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, driver_buff.at(10)*9.6) ;
//				}
				
		
				
			}
	}
	recStatus = ReceiveHeader;
	
}







