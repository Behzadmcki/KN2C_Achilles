#ifndef _FUNC
#define _FUNC


extern char UART_bufferfbus[100];
extern float Filtered_value;
extern float Last_value;

//extern union _ch2int ;
extern void hiphop();
extern int Read_ADC(unsigned char adc_channel);  //uint8_t
extern void gas_data( char gas);  //uint16_t
extern void UART_send_Dyna_buffer(int length);
extern void putchardyna(char ch);
extern void set_goal_postion(char id,char high,char low);
extern void go_to_postion(char id,float deg);
extern void dyna_wheel(char id,char dir,int speed);
extern void get_Buffer (void);
extern void Gripper_action (void);
extern void dyna_wheel(char id,char dir,int speed);
extern void Head_pos (void);
extern void Switch_12 (void);
extern void Roll_pos (void);
extern void Termal_power (void);
extern void LED_power (void);
extern void Do_Action(void);
extern void Do_not_Action (void);
			

#endif