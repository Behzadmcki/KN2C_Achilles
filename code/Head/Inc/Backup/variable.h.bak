#ifndef _VAR
#define	_VAR

#include "Bus.hpp"

 
#define busy 0
#define ready 1


#define TIMCallBack   void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
#define TxCallBack    void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
#define RxCallBack    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 


#define ReceiveHeader false
#define ReceiveData  true


#define FDBMode           3
#define HEDMode           4


#define globalDriverAD  0x20+5


#define Toggle_LED_blue		HAL_GPIO_TogglePin(LED1_GPIO_Port , LED1_Pin)
#define Toggle_LED_red		HAL_GPIO_TogglePin(LED2_GPIO_Port , LED2_Pin)

#define WritePin_LED_red		HAL_GPIO_WritePin(LED1_GPIO_Port , LED1_Pin,GPIO_PIN_SET)
#define WritePin_LED_blue		HAL_GPIO_WritePin(LED2_GPIO_Port , LED2_Pin,GPIO_PIN_SET)

#define EN_ADM_Set        HAL_GPIO_WritePin (BUS_EN_MAX_GPIO_Port ,BUS_EN_MAX_Pin ,GPIO_PIN_SET )
#define EN_ADM_Reset      HAL_GPIO_WritePin (BUS_EN_MAX_GPIO_Port ,BUS_EN_MAX_Pin ,GPIO_PIN_RESET )




extern HeaderPacket  HED_pkg;
extern HeaderPacket  FDB_pkg;
extern BUS bus;



extern int test	;
extern int test2	;
extern int test3 ;
extern int dastan;
extern int headerCounter;
extern int fillCounter;
extern uint8_t recHeader;
extern uint8_t recData[12];
extern uint8_t sendBuffer[20];
extern int headerMode;
extern int vectorCheck[35];
extern int timer;
extern int recieveCheckSum; 
extern int sendCheckSum;
extern int recStatus;
extern int packetSize;
extern int headerSize;
extern uint16_t adcValue[3];
extern int SendStatus;
extern int Head_Command[8];
extern int Data_gas;
extern int firstIRQ;
extern int Global_Connection_CNT ;
extern int global_validation;
extern int	SendStatus ;




#endif





