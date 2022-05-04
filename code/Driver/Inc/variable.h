#ifndef _VAR
#define	_VAR

#include "stm32f4xx_hal.h"
#include "Bus.hpp"
#include "Motor.h"
#include "IMU.hpp"


#define ConnectionLimit  50
 
#define busy 0
#define ready 1


#define TIMCallBack   void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
#define TxCallBack    void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
#define RxCallBack    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 


#define MotorBusy  0
#define MotorReady 1


#define ReceiveHeader false
#define ReceiveData  true



#define SettingType1 1
#define SettingType2 2
#define SettingType3 3

#define disconnect        0
#define PWMMode           1




#define Stop_Mode     58
#define Forward_Mode  59
#define Reverse_Mode  60

#define Motor1_AD   1
#define Motor2_AD   2
#define Motor3_AD   3



#define BusUsart    &huart4


#define		Slave1_AD				0x20+1
#define		Rm1_ID					1
#define		Rm2_ID					2
#define		FF_ID						3


#define		Slave2_AD				0x20+2
#define		Lm1_ID					1
#define		Lm2_ID					2
#define		BF_ID						3

#define		Slave3_AD				0x20+3
#define		A0_ID						1
#define		A1_ID						2
#define		A2_ID						3

#define 	Slave4_AD				0x20+4
#define		Pr_ID						1
#define		Roll_ID					2
#define		Pitch_ID				3


#define   Rm1_inv        true    
#define   Rm2_inv      	 true    
#define   FF_inv         false 
	
#define   Lm1_inv        false     
#define		Lm2_inv				 false	    
#define   BF_inv         false  

#define   A0_inv         true
#define   A1_inv         true
#define   A2_inv         true
	
#define   Pr_inv         true
#define   Roll_inv       false
#define   Pitch_inv      true
	




#define Toggle_LED_blue		HAL_GPIO_TogglePin(LED1_GPIO_Port , LED1_Pin)
#define Toggle_LED_red		HAL_GPIO_TogglePin(LED2_GPIO_Port , LED2_Pin)

#define WritePin_LED_red		HAL_GPIO_WritePin(LED1_GPIO_Port , LED1_Pin,GPIO_PIN_SET)
#define WritePin_LED_blue		HAL_GPIO_WritePin(LED2_GPIO_Port , LED2_Pin,GPIO_PIN_SET)

#define EN_ADM_Set        HAL_GPIO_WritePin (En_Max_GPIO_Port ,En_Max_Pin ,GPIO_PIN_SET )
#define EN_ADM_Reset      HAL_GPIO_WritePin (En_Max_GPIO_Port ,En_Max_Pin ,GPIO_PIN_RESET )

#define INA_Set           HAL_GPIO_WritePin (GPIO_Port_ENA ,GPIO_Pin_ENA ,GPIO_PIN_SET )
#define INB_Reset         HAL_GPIO_WritePin (GPIO_Port_ENB ,GPIO_Pin_ENB ,GPIO_PIN_RESET )

#define INB_Set           HAL_GPIO_WritePin (GPIO_Port_ENB ,GPIO_Pin_ENB ,GPIO_PIN_SET )
#define INA_Reset         HAL_GPIO_WritePin (GPIO_Port_ENA ,GPIO_Pin_ENA ,GPIO_PIN_RESET )





extern BUS bus;

extern HeaderPacket  PWM_pkg;        


extern int headerCounter;
extern int fillCounter;
extern uint8_t recHeader;
extern uint8_t recData[12];
extern uint8_t sendBuffer[20];
extern int headerMode;
extern int vectorCheck[35];
extern int vectorCheck1;
extern int vectorCheck2;
extern int vectorCheck3;
extern int vectorCheck4;
extern int vectorCheck5;
extern int vectorCheck6;
extern int vectorCheck7;
extern int vectorCheck8;
extern int vectorCheck9;
extern int vectorCheck10;
extern int vectorCheck11;
extern int vectorCheck12;
extern int vectorCheck13;
extern int vectorCheck14;
extern int vectorCheck15;
extern int dastan;

extern int globalDriverAD  ;
extern int recieveCheckSum; 
extern int sendCheckSum;
extern int recStatus;
extern int packetSize;
extern int headerSize;
extern int settingType;



//  MOTOR
extern int checkConnection;
extern int motorInv[4][3];
extern int motorTimer;





#endif





