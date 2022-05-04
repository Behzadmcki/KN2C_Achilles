#ifndef _DEF
#define	_DEF


#define 	feedback_packet_size	9


#define		Rx_callback								void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
#define		Tx_callback								void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
#define		TIM_callback							void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*htim)


#define 	ADM485_output_mode				HAL_GPIO_WritePin(BUS_EN_MAX_GPIO_Port,BUS_EN_MAX_Pin,GPIO_PIN_SET)
#define 	ADM485_input_mode					HAL_GPIO_WritePin(BUS_EN_MAX_GPIO_Port,BUS_EN_MAX_Pin,GPIO_PIN_RESET)
                                    

#define		Toggle_led_red 				  	HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin) 
#define		Toggle_led_blue						HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin) 

#define 	busy									0
#define		ready									1

#define		valid									1
#define		unvalid								0



#define		Head_packet_id				1
#define		FDB_packet_id					2

/****************************************/
#define		forward								59 
#define		reverse								60 
#define		motor_stop						58 


#define		first_Data						1
#define 	second_Data						2
#define 	third_Data						3





#define		disconnect						0
#define 	Head_mode							1


#define   FILTER_gas          1/(2*3.14*F_CUT_gas)
#define   DT                  0.005    //s
#define   F_CUT_gas           2


////////////Gripper///////////////
#define   turn_on               29
#define   turn_off              129
#define   GR_POWER_ON           HAL_GPIO_WritePin(Servo_16_EN_GPIO_Port,Servo_16_EN_Pin,GPIO_PIN_SET)
#define   GR_POWER_OFF	        HAL_GPIO_WritePin(Servo_16_EN_GPIO_Port,Servo_16_EN_Pin,GPIO_PIN_RESET)
#define   Termal_power_ON       HAL_GPIO_WritePin(Termal_EN_GPIO_Port,Termal_EN_Pin,GPIO_PIN_SET)
#define   Termal_power_OFF      HAL_GPIO_WritePin(Termal_EN_GPIO_Port,Termal_EN_Pin,GPIO_PIN_RESET)
#define   LED_power_ON          HAL_GPIO_WritePin(LED_EN_GPIO_Port,LED_EN_Pin,GPIO_PIN_SET)
#define   LED_power_OFF         HAL_GPIO_WritePin(LED_EN_GPIO_Port,LED_EN_Pin,GPIO_PIN_RESET)
#define   power_12_ON           HAL_GPIO_WritePin(Servo_12_EN_GPIO_Port,Servo_12_EN_Pin,GPIO_PIN_SET)
#define   power_12_OFF          HAL_GPIO_WritePin(Servo_12_EN_GPIO_Port,Servo_12_EN_Pin,GPIO_PIN_RESET)





#endif







