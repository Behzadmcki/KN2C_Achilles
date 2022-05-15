
/**********************************  LED CONTROL  ***********************************************/

#define    led_yellow_on          		 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,0)
#define    led_yellow_off         		 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,1)      
#define    led_red_on       	   	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0)  
#define    led_red_off       	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1)   
#define    led_yellow_toggle    				HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_7)
#define    led_red_toggle   			HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_0) 



/************************************** bus_control *********************************************/

#define    rx_mode                HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,0)
#define    tx_mode                HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,1)




#define 	F_CUT_STB								5.0f
#define 	FILTER_ROLL							1/(2*3.14*F_CUT_STB)
#define 	FILTER_PITCH						1/(2*3.14*F_CUT_STB)







