#include "Motor.h"
#include "Math.h"


MOTOR motor1(1);
MOTOR motor2(2);
MOTOR motor3(3);


MOTOR::MOTOR ()
{
	
}
MOTOR::MOTOR(int _motorAD)
{
	motorAD = _motorAD;
}


void MOTOR::MotorInit (void)
{
	
	HAL_GPIO_WritePin(MFan_En_GPIO_Port,MFan_En_Pin,GPIO_PIN_SET) ;			//FAN 
	HAL_TIM_Base_Start_IT (&htim12);
	motor1.MotorSetting();
	motor2.MotorSetting();
	motor3.MotorSetting();
	
	
}


void MOTOR::MotorSetting(void)
{

			switch(globalDriverAD)
			{
				case Slave1_AD:
						SlaveSetting1();
		        break;                          		
				case Slave2_AD:
						SlaveSetting2();
				    break;
 
				case Slave3_AD:
						SlaveSetting3();
				    break;
				
				case Slave4_AD:
						SlaveSetting4();
				    break;
			};
			MotorInv(globalDriverAD ,motorAD);
				
}

		
void MOTOR::SlaveSetting1(void)
{
	  switch (motorAD )
		{
			case Rm1_ID:
				PWMSetting (SettingType1);
			  FilterSetting( &PWMFilterVar,5 ,0.005 );
			  break;
			case Rm2_ID:
				PWMSetting (SettingType2);
			FilterSetting(&PWMFilterVar,5 ,0.005 );
			  break;
			case FF_ID:
				PWMSetting (SettingType3);
			FilterSetting(&PWMFilterVar,5 ,0.005 );
			  break;
			
		};
		
}
void MOTOR::SlaveSetting2(void)
{
	  switch (motorAD )
		{
			case Lm1_ID:
			  PWMSetting (SettingType2);
			  FilterSetting(&PWMFilterVar,5 ,0.005 );
			  break;
			case Lm2_ID:
				PWMSetting (SettingType1);
			FilterSetting(&PWMFilterVar,5 ,0.005 );
			  break;
			case BF_ID:
				PWMSetting (SettingType3);
			FilterSetting(&PWMFilterVar,5 ,0.005 );
			  break;
			
		};
}
void MOTOR::SlaveSetting3(void)
{
	 FilterSetting(&PWMFilterVar ,5 ,0.005 );
	  switch (motorAD )
		{
			case A0_ID:
				PWMSetting (SettingType3);
			  break;
			case A1_ID:
				PWMSetting (SettingType2);
			  break;
			case A2_ID:
				PWMSetting (SettingType1);
			  break;
			
		};
}
void MOTOR::SlaveSetting4(void)
{
	  FilterSetting(&PWMFilterVar ,2 ,0.005 );
    switch (motorAD )
		{
			case Pr_ID:
			  PWMSetting (SettingType1);
			  break;
			case Roll_ID:
				PWMSetting (SettingType3);
			  break;
			case Pitch_ID:
				PWMSetting (SettingType2);
			  break;
			
		};
}




void MOTOR::PWMSetting(int settingType)
{
	if(settingType == 1)
	{
		GPIO_Port_ENA = INA_1_GPIO_Port ;
		GPIO_Pin_ENA = INA_1_Pin ;
		
		GPIO_Port_ENB = INB_1_GPIO_Port ;
		GPIO_Pin_ENB = INB_1_Pin ;
		
		timerType = &htim5 ;  
		timerChannel = TIM_CHANNEL_3 ;
	}
		else if(settingType == 2)
	{
		GPIO_Port_ENA = INA_3_GPIO_Port ;
		GPIO_Pin_ENA = INA_3_Pin ;
		
		GPIO_Port_ENB = INB_3_GPIO_Port ;
		GPIO_Pin_ENB = INB_3_Pin ;
		
		timerType = &htim9 ;
		timerChannel = TIM_CHANNEL_1 ;
	}
	else if(settingType == 3)
	{
		GPIO_Port_ENA = INA_2_GPIO_Port ;
		GPIO_Pin_ENA = INA_2_Pin ;
		
		GPIO_Port_ENB = INB_2_GPIO_Port ;
		GPIO_Pin_ENB = INB_2_Pin ;
		
		timerType = &htim4 ;
		timerChannel = TIM_CHANNEL_3 ;
		
	}

	

	HAL_TIM_PWM_Start(timerType,timerChannel) ;
}
void MOTOR::MotorInv(int _globalDriverAD,int _motorAD)
{
	motorInv[Slave1_AD -(0x20+1)][Rm1_ID-1] = Rm1_inv;
	motorInv[Slave1_AD -(0x20+1)][Rm2_ID-1] = Rm2_inv;
	motorInv[Slave1_AD -(0x20+1)][FF_ID-1] = FF_inv;
	motorInv[Slave2_AD -(0x20+1)][Lm1_ID-1] = Lm1_inv;
	motorInv[Slave2_AD -(0x20+1)][Lm2_ID-1] = Lm2_inv;
	motorInv[Slave2_AD -(0x20+1)][BF_ID-1] = BF_inv;
	motorInv[Slave3_AD -(0x20+1)][A0_ID-1] = A0_inv;
	motorInv[Slave3_AD -(0x20+1)][A1_ID-1] = A1_inv;
	motorInv[Slave3_AD -(0x20+1)][A2_ID-1] = A2_inv;
	motorInv[Slave4_AD -(0x20+1)][Pr_ID-1] = Pr_inv;
	motorInv[Slave4_AD -(0x20+1)][Roll_ID-1] = Roll_inv;
	motorInv[Slave4_AD -(0x20+1)][Pitch_ID-1] = Pitch_inv;
	
	mainMotorInv = motorInv[_globalDriverAD-(0x20+1)][_motorAD-1];
}



////////////////// while

void MOTOR::MotorAction(void)
{
	
	motorTimer = MotorBusy;
	motor3.MotorStart();
	motor1.MotorStart();
	motor2.MotorStart();
	
}		
void MOTOR::MotorStart()
{

	
	MotorData(); 
	MotorMove ();
}


void MOTOR::CheckConnection()
{

	if (checkConnection >ConnectionLimit)
	{
		motor1.motorMode = disconnect;
		motor2.motorMode = disconnect;
		motor3.motorMode = disconnect;
		checkConnection = 52;
	}
	checkConnection ++;
}
void MOTOR::MotorData ()
{

	switch(motorMode )
	{
		case PWMMode:
		{
			switch(motorAD )
			{
				case Motor1_AD :
				 
		    	motorData[0] = bus.driver_buff.at(5);
			    motorData[1] = bus.driver_buff.at(6);
			    break;
				case Motor2_AD :
					motorData[0] = bus.driver_buff.at(7);
					motorData[1] = bus.driver_buff.at(8);
					break;
				case Motor3_AD:
					motorData[0] = bus.driver_buff.at(9);
					motorData[1] = bus.driver_buff.at(10);
					break;
			};
			break;
		}
		
		case disconnect:
 
		{
			motorData[0] =  Stop_Mode  ;
			motorData[1] = 255;
			break;
		}
		
	};
}

void MOTOR::FilterSetting(struct FilterVar *_filterVar,float _F_CUT,float _DT )
{
  
  _filterVar->FILTER=1/(2*3.14*_F_CUT);	
	_filterVar->DT = _DT;
	_filterVar->F_CUT = _F_CUT ;
	
}
void MOTOR::DoFilter(struct FilterVar *FilterVar)
{
	FilterVar->Filtered_PWM=FilterVar->Last_PWM +  ((float)FilterVar->DT / ((float)FilterVar->FILTER )+(float)FilterVar->DT)*(9.41*motorData[1]-FilterVar->Last_PWM);
	FilterVar->Last_PWM = FilterVar->Filtered_PWM ;
	FilterVar->Filtered_PWM=std::ceil(FilterVar->Filtered_PWM) ;
}
	
void MOTOR::MotorMove(void)
{
	
		switch(motorMode)
		{
			case PWMMode:
				DoFilter (&PWMFilterVar );
				motorDirection = motorData[0];
				motorPWM = PWMFilterVar.Filtered_PWM ;
			  break;
			case disconnect:
				motorDirection = Stop_Mode ;
				motorPWM = 2400;
		  	break;
		};
 	
  
	switch(motorDirection )
	{
		case Stop_Mode:
		    HAL_GPIO_WritePin (GPIO_Port_ENA ,GPIO_Pin_ENA ,GPIO_PIN_SET );
		    HAL_GPIO_WritePin (GPIO_Port_ENB ,GPIO_Pin_ENB ,GPIO_PIN_SET );
		    motorPWM = 2400;
		   
        break;
		case Forward_Mode:
				if(mainMotorInv )
				{
					HAL_GPIO_WritePin (GPIO_Port_ENA ,GPIO_Pin_ENA ,GPIO_PIN_RESET );
				  HAL_GPIO_WritePin (GPIO_Port_ENB ,GPIO_Pin_ENB ,GPIO_PIN_SET );
				}
				else
				{
					 HAL_GPIO_WritePin (GPIO_Port_ENA ,GPIO_Pin_ENA ,GPIO_PIN_SET );
				  HAL_GPIO_WritePin (GPIO_Port_ENB ,GPIO_Pin_ENB ,GPIO_PIN_RESET );
				}
         break;
		case Reverse_Mode:
				if(mainMotorInv )
				{
					HAL_GPIO_WritePin (GPIO_Port_ENA ,GPIO_Pin_ENA ,GPIO_PIN_SET );
				  HAL_GPIO_WritePin (GPIO_Port_ENB ,GPIO_Pin_ENB ,GPIO_PIN_RESET );
				}
				else
				{
					HAL_GPIO_WritePin (GPIO_Port_ENA ,GPIO_Pin_ENA ,GPIO_PIN_RESET );
				  HAL_GPIO_WritePin (GPIO_Port_ENB ,GPIO_Pin_ENB ,GPIO_PIN_SET );
				}
	       break;
		};
	
	__HAL_TIM_SET_COMPARE(timerType,timerChannel, (uint32_t)motorPWM   ) ;
		

}

