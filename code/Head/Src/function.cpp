#include "function.h"
#include <Define.h>
#include "stm32f0xx_hal.h"
#include "adc.h"
#include "usart.h"
#include "main.h"
#include "variable.h"


char UART_bufferfbus[100];

	
float Filtered_value;
float Last_value;

union _ch2int 
{
    int16_t real;
    char byte[2];
};

typedef union _ch2int  ch2int;


void hiphop()
{
  int i,j,k;
	


  for(i=0;i<6;i++)
    {

			Toggle_led_blue ;
			Toggle_led_red ;
			HAL_Delay(100);
			
			
    } 
}

int Read_ADC(unsigned char adc_channel)
{
		
	ADC_ChannelConfTypeDef sConfig;
	sConfig.Channel = adc_channel;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	
	
	uint16_t tmp;
	HAL_ADC_Start(&hadc);
	while(HAL_ADC_PollForConversion(&hadc,100) != 0);
	tmp = HAL_ADC_GetValue(&hadc);
	HAL_ADC_Stop(&hadc);
	
	return tmp;

}

void gas_data(char gas)
	{
	gas = Read_ADC (ADC_CHANNEL_0);
  }



void UART_send_Dyna_buffer(int length)
	{
		HAL_UART_Transmit(&huart1,(uint8_t*)UART_bufferfbus,length,1); 
	}
	
	


void putchardyna(char ch)
	{
		UART_bufferfbus[0]=ch;
		UART_send_Dyna_buffer(1);
	}
	
	


 void set_goal_postion(char id,char high,char low)
{
	
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
		unsigned char check_sum=0; 
		HAL_Delay(1);
		HAL_Delay(1);	
    putchardyna(0xff);  
    HAL_Delay(1);
    putchardyna(0xff);
		HAL_Delay(1);
    putchardyna(id);
		HAL_Delay(1);
    putchardyna(0x05);
		HAL_Delay(1);
    putchardyna(0x03);
		HAL_Delay(1);
    putchardyna(0x1e);
		HAL_Delay(1);
    putchardyna(low);
		HAL_Delay(1);
    putchardyna(high);
		HAL_Delay(1);
    check_sum=~(id+0x05+0x03+0x1e + low+high);
    putchardyna(check_sum);             
    HAL_Delay(3);
		//  delay_ms(3);*/
		//   servo_talk;  
}

void go_to_postion(char id,float deg)
{
    ch2int goal; 

    goal.real=(int)((float)((float)(deg+60)*1023.0f)/300.0f);    
    set_goal_postion(id,goal.byte[1],goal.byte[0]); 

}


void get_Buffer (void)
{
	for(int i=0;i<8;i++)
	  Head_Command[i]=bus.driver_buff.at(i+4);
}



void Gripper_action (void)
{

  if(Head_Command[0]==turn_on || Head_Command[0]==turn_off)
	{      
      
          if(Head_Command[0]==turn_on)
            {
              GR_POWER_ON; 
            }
          else if(Head_Command[0]==turn_off )
            {
              GR_POWER_OFF;
            }
	}  
  dyna_wheel(1,Head_Command[1],1023);
    
	}				
						
  
void dyna_wheel(char id,char dir,int speed){//max speed:1023
//    if(last_dyna_wheel!=dir){
//      for(int j=0;j<5;j++){
        char coml=0,comh=0;
        if(dir==forward){
          comh=(speed/256)+4;
          coml=speed%256;
        }
        else if(dir==reverse){
          comh=(speed/256);
          coml=speed%256;
        }
        else {
          coml=0;
          comh=0;
        }
        HAL_Delay(1);  
        putchardyna(0xff);  
        putchardyna(0xff);
        putchardyna(id);
        putchardyna(0x05);
        putchardyna(0x03);
        putchardyna(0x20);
        putchardyna(coml);
        putchardyna(comh);
        uint8_t check_sum=~(id+0x05+0x03+0x20+coml+comh);
        putchardyna(check_sum);             
        HAL_Delay(1);
//      }
//    }
}

void Head_pos (void)
{
		go_to_postion(3,Head_Command[2]);    //pitch
  	go_to_postion(4,Head_Command[3]);    //yaw
}

void Termal_power (void)
{
		if(Head_Command[4]==turn_on)
			Termal_power_ON;
		else if(Head_Command[4]==turn_off)
			Termal_power_OFF;
}

void LED_power (void)
{
		if(Head_Command[5]==turn_on)
			LED_power_ON;
		else if(Head_Command[5]==turn_off)
			LED_power_OFF;		
}

void Roll_pos (void)
{
		go_to_postion(2,Head_Command[6]);    //roll
}

void Switch_12 (void)
{
		if(Head_Command[7]==turn_on)
			power_12_ON;
		else if(Head_Command[7]==turn_off)
			power_12_OFF;
}

void filter_gas_data(void)
{
	test=Read_ADC(ADC_CHANNEL_0);
Filtered_value=Last_value  +  ((float)DT / ((float)FILTER_gas )+(float)DT)*(Read_ADC(ADC_CHANNEL_0)/16-Last_value);
  Last_value = Filtered_value ;
	Data_gas = Filtered_value;
}
void Do_Action(void)
{ 
	
	  get_Buffer();
		Head_pos();
	  Termal_power();
	  LED_power();
	  filter_gas_data();
	  Gripper_action();
	  Switch_12();
	  Roll_pos();
}

void Do_not_Action (void)
{
	  GR_POWER_OFF;
}





	
//float y1,y2,y3,x1,x2,x3,a=0,b=0,c=0;
//int n=0,set_adc,true_data=0;

//float get_zarib_pot(char AD_driver, uint16_t adc_value)
//{
//		true_data=0;
//		if(AD_driver==1)
//		{
//			y1=10;
//			y2=20;
//			y3=30;			
//		}
//		else if(AD_driver==2)
//		{
//			y1=10;
//			y2=20;
//			y3=30;			
//		}
//		else if(AD_driver==3)
//		{
//			y1=10;
//			y2=20;
//			y3=30;
//		}
//		
//		if(n==0 && set_adc==1)
//		{
//			x1=adc_value;
//			n++;
//			set_adc=0;
//		}
//		else if(n==1 && set_adc==1)
//		{
//			x2=adc_value;
//			n++;
//			set_adc=0;
//		}
//		else if(n==2 && set_adc==1)
//		{
//			x1=adc_value;
//			n=0;
//			set_adc=0;
//			true_data=1;
//		}
//		
//		a=( y1*(x2-x3) + y2*(x3-x1) + y3*(x1-x2) ) / ( x1*x1*(x2-x3) + x2*x2*(x3-x1) + x3*x3*(x1-x2) );
//		b=( x1*x1*(y2-y3) + x2*x2*(y3-y1) + x3*x3*(y1-y2) ) / ( x1*x1*(x2-x3) + x2*x2*(x3-x1) + x3*x3*(x1-x2) );
//		c=( x1*x1*(x2*y3 - x3*y2) + x2*x2*(y1*x3 - x1*y3) + x3*x3*(x1*y2 - y1*x2) ) / ( x1*x1*(x2-x3) + x2*x2*(x3-x1) + x3*x3*(x1-x2) );
//		
//		
//{










