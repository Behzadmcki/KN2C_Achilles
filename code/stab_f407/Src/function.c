#include <function.h>
#include "i2c.h"
#include <Global_variable.h>




void hiphop(void)
{
  int i,j,k;

			led_yellow_off;
			led_red_off;
	
  for(i=0;i<6;i++)
    {
			led_yellow_toggle;
			led_red_toggle;
			HAL_Delay(100);	
    } 
}





void UART_send_Dyna_buffer(int length)
	{
		HAL_UART_Transmit(&huart2,(uint8_t*)UART_bufferfbus,length,1); 
	}
	
	


void putchardyna(char ch)
	{
		UART_bufferfbus[0]=ch;
		UART_send_Dyna_buffer(1);
	}
	
	


 void set_goal_postion(char id,char high,char low)
{
		unsigned char check_sum=0; 
		HAL_Delay(1);
		//HAL_Delay(1);	
    putchardyna(0xff);  
    //HAL_Delay(1);
    putchardyna(0xff);
		//HAL_Delay(1);
    putchardyna(id);
		//HAL_Delay(1);
    putchardyna(0x05);
		//HAL_Delay(1);
    putchardyna(0x03);
		//HAL_Delay(1);
    putchardyna(0x1e);
		//HAL_Delay(1);
    putchardyna(low);
		//HAL_Delay(1);
    putchardyna(high);
		//HAL_Delay(1);
    check_sum=~(id+0x05+0x03+0x1e + low+high);
    putchardyna(check_sum);             
    HAL_Delay(1);
		//  delay_ms(3);*/
		//   servo_talk;  
}

void read_moving_speed(char id)
{
	
	
	
		unsigned char check_sum=0; 
		HAL_Delay(1);
		//HAL_Delay(1);	
    putchardyna(0xff);  
    //HAL_Delay(1);
    putchardyna(0xff);
		//HAL_Delay(1);
    putchardyna(id);
		//HAL_Delay(1);
    putchardyna(0x04);
		//HAL_Delay(1);
    putchardyna(0x02);
		//HAL_Delay(1);
    putchardyna(0x2a);
		//HAL_Delay(1);
//    putchardyna(low);
		//HAL_Delay(1);
//    putchardyna(high);
		//HAL_Delay(1);
    check_sum=~(id+0x04+0x02+0x2a);
    putchardyna(check_sum);             
    HAL_Delay(1);
		//  delay_ms(3);*/
		//   servo_talk; 
		
		
		
}




void go_to_postion(char id,float deg)
{
		tx_mode;
    ch2int goal; 
    goal.real=(int)((float)((float)deg*1023.0f)/300.0f);    
    set_goal_postion(id,goal.byte[1],goal.byte[0]); 
}
/*void filter_lowpass(void){
	filter_roll=last_roll + ((float)DT / ((float)FILTER_ROLL )+(float)DT)*(Mahony.Roll - last_roll);     
  last_roll=filter_roll;
	filter_pitch=last_pitch + ((float)DT / ((float)FILTER_PITCH )+(float)DT)*(Mahony.Pitch - last_pitch);     
  last_pitch=filter_pitch;	
}*/
void write_data_2_upboard(MPU_SENSOR *sen)
{
	tx_mode;
	uint8_t tx[24];
	uint8_t sum=0;
	send[0].f=sen->acc_x;
	send[1].f=sen->acc_y;
	send[2].f=sen->acc_z;
	send[3].f=sen->gyro_x;
	send[4].f=sen->gyro_y;
	send[5].f=sen->gyro_z;
	build_packet(tx,send);
	uart_tx_bus_buffer[0]='%';
	uart_tx_bus_buffer[1]='^';
	for(int j=2;j<26;j++){
		uart_tx_bus_buffer[j]=tx[j-2];
		sum+=uart_tx_bus_buffer[j];
	}
	uart_tx_bus_buffer[26]= sum%256;
	uart_tx_bus_buffer[27]='\r';
	
	HAL_UART_Transmit(&huart4,uart_tx_bus_buffer,28,100);	
	rx_mode;
	//HAL_Delay(1);					
}

void change_float_2_bytes(uint8_t* snd , data_packet* uni, char i){
	snd+=(i*4);
	uni += i;
	for(int j=0;j<4;j++){
		*snd = uni->c[j];
		snd++;
	}
}
	
void build_packet(uint8_t* snd , data_packet* uni){
	for(int j = 0; j < 6; j++){
		change_float_2_bytes(snd ,uni, j);
	}
}
	
	
	
	
















		

	
	
