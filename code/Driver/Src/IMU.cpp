#include "IMU.hpp"
#include <variable.h>

IMU::IMU()
{

}
IMU::IMU(int _imuId)
{
	imuId=_imuId;	

}
void IMU::IMUInit()
{
 HAL_TIM_Base_Start_IT(&htim7);
 recStatusImu=ReceiveHeader ;
 chooseImu=Imu1id;
 ChooseImu () ;
	HAL_UART_Receive_DMA(&huart3 ,&recHeaderImu,1); 
}

void IMU::GetPacketImu()
{
	
			switch( recStatusImu) 
			{
				case (ReceiveHeader):
				{
					
					 CheckHeaderImu (&Ac_pkg ); //  Acceleration
					 CheckHeaderImu (&Av_pkg ); //  Angular velocity
					 CheckHeaderImu (&An_pkg ); // Angle 
					 
					break;
				}
				case (ReceiveData):
				{
					FillbufferImu();
				  
					break;
				}
			};	
}

void IMU::CheckHeaderImu (struct HeaderPacketImu* HeaderPacketImu)
{
	
	switch (HeaderPacketImu->headerCounterImu )
	{
		case 0:
		{			
			if ( recHeaderImu == HeaderPacketImu ->firstByteImu   )  
        { 
				   HeaderPacketImu->headerCounterImu++; 
				}
			else          										       
				   HeaderPacketImu->headerCounterImu=0;
		  break; 
		}
		case 1:
		{
			
		  if ( recHeaderImu == HeaderPacketImu->secondByteImu )  
        {
															
					 HeaderPacketImu->headerCounterImu=0 ;
			     recStatusImu = ReceiveData ;
				   headerModeImu=HeaderPacketImu->packetIDImu; 
        
           Imu_buff.resize (11 );
           Imu_buff.at (0) = HeaderPacketImu->firstByteImu ;
	         Imu_buff.at (1) = HeaderPacketImu->secondByteImu ;
          
        }
			else if(recHeaderImu == HeaderPacketImu->firstByteImu)  
				HeaderPacketImu->headerCounterImu=1;
			else          
				HeaderPacketImu->headerCounterImu=0;
			break; 
		}

	
	}		
}
	
void IMU::FillbufferImu ( void)
{
	for (int counterImu = 2 ;counterImu < 11 ; counterImu++ )
	{
	     Imu_buff.at(counterImu ) = recDataImu[counterImu - 2] ;
		   switch (headerModeImu)
		   { 
				 case(AcMode):
				 {
					 buff_Ac[counterImu]=Imu_buff.at(counterImu);
					 
					 break;
				 }
					case(AvMode ):
				 {
					 buff_Av[counterImu]=Imu_buff.at(counterImu);
					 
					 break;
				 } 
					case(AnMode ):
				 {
					 buff_An[counterImu]=Imu_buff.at(counterImu);
					 
					 break;
			 }
	   };

	} 
	CheckEndImu ();
}

void IMU::CheckEndImu (void )
{

	recieveCheckSumImu=0;
	for (int i=0 ; i<10 ; i++)
	{
		recieveCheckSumImu += Imu_buff.at(i);
		recieveCheckSumImu%=256 ;
	}
	if (recieveCheckSumImu == Imu_buff.at(10) )  
	   {		
         //  HAL_UART_Receive_DMA(&huart3 ,&recHeaderImu,1); 
						// packet valid	
						switch (ImuPacketCNT)
						{
							case 0:
							{
								if ( headerModeImu == AcMode  )  { ImuPacketCNT++;   }
								else        						ImuPacketCNT=0;
								break; 
							}
							case 1:
							{
							
								if ( headerModeImu == AvMode)  { ImuPacketCNT++; }
								else if(headerModeImu == AcMode )  ImuPacketCNT=1;
								else                                   ImuPacketCNT=0;
								break; 
							}
							case 2:
							{
								if ( headerModeImu == AnMode  )  
								{
									ImuPacketCNT=0; 
									ImuPacketsReceived=ready ;
								  
									__HAL_TIM_SetCounter(&htim7,0) ;
									
								}
							else if(headerModeImu == AcMode )  ImuPacketCNT=1;
							else                                         ImuPacketCNT=0;
							
							break; 
							}
						
							
						 recieveCheckSumImu=0;				 
						 };
     
	 } 

	   	
	 recStatusImu=ReceiveHeader ;	
	
}

void IMU:: MakeparamImu (void)
{
	
	if(chooseImu>2)	chooseImu=1 ;
	switch(chooseImu)
	{
		case(Imu1id):
			
			{
				
		    Imu1.CalculateImu();
				chooseImu=Imu2id ;
			  ChooseImu();
			}
			break;
		
		case(Imu2id):
		   
			 {
		    Imu2.CalculateImu();
				chooseImu=Imu1id ;
				ChooseImu () ;
			 }
		break;
		
//		case(Imu3id):
//		   
//		   {
//				imu.CalculateImu (&Imu3);
//				chooseImu++;
//				ChooseImu() ;
//			 }
//		break;
	};
	
}

void IMU:: CalculateImu (void)
 {
	 
		imuAx=(float)((short int)(buff_Ac[3]<<8)|buff_Ac[2])/32768*16*9.8;
		imuAY=(float)((short int)(buff_Ac[5]<<8)|buff_Ac[4])/32768*16*9.8;
		imuAZ=(float)((short int)(buff_Ac[7]<<8)|buff_Ac[6])/32768*16*9.8;
   
		imuWx=(float)((short int)(buff_Av[3]<<8)|buff_Av[2])/32768*2000;
		imuWy=(float)((short int)(buff_Av[5]<<8)|buff_Av[4])/32768*2000;
		imuWz=(float)((short int)(buff_Av[7]<<8)|buff_Av[6])/32768*2000;

		imuRoll=(float)((short int)(buff_An[3]<<8)|buff_An[2])/32768*180;
		imuPitch=(float)((short int)(buff_An[5]<<8)|buff_An[4])/32768*180;
		imuYaw=(float)((short int)(buff_An[7]<<8)|buff_An[6])/32768*180;
	 
	 
	 filteredWx =lastWx  +  ((float)DT_IMU / ((float)FILTER_IMU )+(float)DT_IMU)*(imuWx - lastWx );
	 lastWx  = filteredWx  ;
	 
	 filteredWy = lastWy  +  ((float)DT_IMU / ((float)FILTER_IMU )+(float)DT_IMU)*( imuWy - lastWy );
	 lastWy  =  filteredWy  ;
	 
	 filteredWz = lastWz  +  ((float)DT_IMU / ((float)FILTER_IMU )+(float)DT_IMU)*( imuWz - lastWz );
	 lastWz  = filteredWz  ;
	 
	 
	 
	 
	 
	 
	 
	   switch(imuId)
		 {
			 case Imu1id:
				Imu1.filteredWy = -Imu1.filteredWy ;
				Imu1.filteredWx  -= offsetWx  ;
			  Imu1.filteredWy  -= offsetWy ;
			  Imu1.filteredWz  -= offsetWz ;
				break; 
			 case Imu2id:
				Imu2.filteredWx = Imu2.filteredWx + Imu1.filteredWy ; 
			 
			  Imu2.filteredWx -= offsetWx ;
			  Imu2.filteredWy -= offsetWy ;
			  Imu2.filteredWz -= offsetWz ;
				break; 
			 case Imu3id:
				 
				break; 
			 
		 };
		 
		 Wyaw1=(float)sqrt(pow(Imu1.filteredWx,2)+pow(Imu1.filteredWz,2));
		 Wyaw2=(float)sqrt(pow(Imu2.filteredWy,2)+pow(Imu2.filteredWz,2));
		 Wyaw=(Wyaw1+Wyaw2)/2 ;
	
 }

 
void IMU::ChooseImu()
 {
	 
	 if(chooseImu>2)	chooseImu = 1 ;
	 
		switch(chooseImu)
		{
			case(Imu1id):
			{        				
        Select_A_Set;
        Select_B_Reset;
        Select_C_Reset;
    break; 
			}
			case(Imu2id):
		  {	
        Select_A_Reset;
        Select_B_Reset;
        Select_C_Reset;
				
		  break;
		  }
			case(Imu3id):
			{
				Select_A_Reset;
        Select_B_Set;
        Select_C_Reset;

				break;
			}
	  };  
	 
		HAL_UART_Receive_DMA(&huart3 ,&recHeaderImu,1);
		 HAL_Delay(5);
		

	}
void IMU::GetImuOffset()
{
	 offsetWx=imuWx;
	 offsetWy=imuWy;
	 offsetWz=imuWz;
	 if (imuId == Imu1id )
	 {
	   offsetWy = -offsetWy;
	 }		 
	
}