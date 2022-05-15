
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "BUS.hpp"
#include "IMU.hpp"
#include <variable.h>

/* USER CODE BEGIN Includes */
 using namespace std ;
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */


//TIMCallBack 
//{
//	if (htim->Instance==TIM12) //  controll timer
//	{
//		motorTimer = MotorReady ;
//	}


//	
//}


RxCallBack 
{


	if(huart->Instance==UART4 )  // bus
	{
    	bus.GetPacket();
		
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);	


			if( recStatus == ReceiveHeader)
			{
				HAL_UART_Receive_IT(BusUsart ,&recHeader,1); 
			}
			else if (recStatus == ReceiveData)
			{
				HAL_UART_Receive_IT(BusUsart  ,recData ,packetSize - headerSize );
			}				
	}

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
 
 

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_UART4_Init();
  MX_TIM4_Init();
  MX_TIM9_Init();
  MX_ADC1_Init();
  MX_TIM5_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
	MX_TIM12_Init();
	
	HAL_TIM_Base_Start(&htim4);
	HAL_TIM_Base_Start(&htim5);
	HAL_TIM_Base_Start(&htim9);
	
	
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);


	


  /* USER CODE BEGIN 2 */
 
 BUS::BusInit();
HAL_UART_Receive_IT(BusUsart ,&recHeader,1); 

// HAL_TIM_Base_Start_IT (&htim12);
 
// 		__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, 2400) ;
//		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, 2400) ;
//		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, 2400) ;
//		TIM4->CCR3 = 2400;
//		TIM5->CCR3 = 2400;
//		TIM9->CCR1 = 2400;

// MOTOR::MotorInit();
 
//	HAL_GPIO_WritePin(PWM_3_GPIO_Port, PWM_3_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(PWM_2_GPIO_Port, PWM_2_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(PWM_1_GPIO_Port, PWM_1_Pin, GPIO_PIN_SET);


 /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

		
  /* USER CODE BEGIN 3 */
		

		
		
		if(dastan==1)
		{
					dastan=0;

			if(vectorCheck[5]== Forward_Mode)
				{
					HAL_GPIO_WritePin(INA_3_GPIO_Port,INA_3_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(INB_3_GPIO_Port,INB_3_Pin,GPIO_PIN_RESET);
					__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, uint32_t(vectorCheck[6]*18.89)) ;
//					__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, 2400) ;

				}
				else if(vectorCheck[5]==Reverse_Mode)
				{
					HAL_GPIO_WritePin(INA_3_GPIO_Port,INA_3_Pin,GPIO_PIN_RESET);
		      HAL_GPIO_WritePin(INB_3_GPIO_Port,INB_3_Pin,GPIO_PIN_SET);
					__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, uint32_t(vectorCheck[6]*18.89)) ;
//					__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, 2400) ;
				}
				else
				{
					HAL_GPIO_WritePin(INA_3_GPIO_Port,INA_3_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(INB_3_GPIO_Port,INB_3_Pin,GPIO_PIN_SET);
					__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, uint32_t(vectorCheck[6]*18.89)) ;
//					__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, 2400) ;
					
				}
				
				
				if(vectorCheck[7]== Forward_Mode)
				{
					HAL_GPIO_WritePin(INA_2_GPIO_Port,INA_2_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(INB_2_GPIO_Port,INB_2_Pin,GPIO_PIN_RESET);
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, uint32_t(vectorCheck[8]*18.89)) ;
//					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, 2400) ;
				}
				else if(vectorCheck[7]==Reverse_Mode)
				{
					HAL_GPIO_WritePin(INA_2_GPIO_Port,INA_2_Pin,GPIO_PIN_RESET);
		      HAL_GPIO_WritePin(INB_2_GPIO_Port,INB_2_Pin,GPIO_PIN_SET);
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, int32_t(vectorCheck[8]*18.89)) ;
//					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, 2400) ;

				}
				else
				{
					HAL_GPIO_WritePin(INA_2_GPIO_Port,INA_2_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(INB_2_GPIO_Port,INB_2_Pin,GPIO_PIN_SET);
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, int32_t(vectorCheck[8]*18.89)) ;
//					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, 2400) ;

				}
				
				if(vectorCheck[9]== Forward_Mode)
				{
					HAL_GPIO_WritePin(INA_1_GPIO_Port,INA_1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(INB_1_GPIO_Port,INB_1_Pin,GPIO_PIN_RESET);
					__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, int32_t(vectorCheck[10]*18.89)) ;
//					__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, 2400) ;

				}
				else if(vectorCheck[9]==Reverse_Mode)
				{
					HAL_GPIO_WritePin(INA_1_GPIO_Port,INA_1_Pin,GPIO_PIN_RESET);
		      HAL_GPIO_WritePin(INB_1_GPIO_Port,INB_1_Pin,GPIO_PIN_SET);
					__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, int32_t(vectorCheck[10]*18.89)) ;
//					__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, 2400) ;
				}
				else
				{
					HAL_GPIO_WritePin(INA_1_GPIO_Port,INA_1_Pin,GPIO_PIN_SET);
					HAL_GPIO_WritePin(INB_1_GPIO_Port,INB_1_Pin,GPIO_PIN_SET);
					__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, int32_t(vectorCheck[10]*18.89)) ;
//					__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, 2400) ;
				}
				
		}
		
		
//		HAL_GPIO_WritePin(INA_1_GPIO_Port,INA_1_Pin,GPIO_PIN_SET);
//		HAL_GPIO_WritePin(INB_1_GPIO_Port,INB_1_Pin,GPIO_PIN_RESET);
//	__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, 2400) ;

//		HAL_GPIO_WritePin(INA_2_GPIO_Port,INA_2_Pin,GPIO_PIN_SET);
//		HAL_GPIO_WritePin(INB_2_GPIO_Port,INB_2_Pin,GPIO_PIN_RESET);
//	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, 2400) ;
//		
//		HAL_GPIO_WritePin(INA_3_GPIO_Port,INA_3_Pin,GPIO_PIN_SET);
//		HAL_GPIO_WritePin(INB_3_GPIO_Port,INB_3_Pin,GPIO_PIN_RESET);
//	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, 2400) ;
//		
//HAL_Delay(2000);
//		
//		
//		HAL_GPIO_WritePin(INA_1_GPIO_Port,INA_1_Pin,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(INB_1_GPIO_Port,INB_1_Pin,GPIO_PIN_SET);
//	__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3, 2400) ;

//		HAL_GPIO_WritePin(INA_2_GPIO_Port,INA_2_Pin,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(INB_2_GPIO_Port,INB_2_Pin,GPIO_PIN_SET);
//	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, 2400) ;
//		
//		HAL_GPIO_WritePin(INA_3_GPIO_Port,INA_3_Pin,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(INB_3_GPIO_Port,INB_3_Pin,GPIO_PIN_SET);
//	__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1, 2400) ;


//HAL_Delay(2000);





// 			if (motorTimer == MotorReady  )
//			{ 
//					MOTOR::CheckConnection(); 
//					MOTOR::MotorAction();
//			}

			if(checkConnection > ConnectionLimit  )
			{
					if( recStatus == ReceiveHeader)
					{
						HAL_UART_Receive_IT(&huart4 ,&recHeader,1); 
					}
					else if (recStatus == ReceiveData)
					{
						HAL_UART_Receive_IT(&huart4 ,recData ,packetSize - headerSize );
					}				
			}
			
  }
	
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
