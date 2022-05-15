#include <Global_variable.h>


void hiphop(void);


void UART_send_Dyna_buffer(int length);


void putchardyna(char ch);


void set_goal_postion(char id,char high,char low);


void go_to_postion(char id,float deg);


void write_data_2_upboard(MPU_SENSOR *sen);


void change_float_2_bytes(uint8_t* snd , data_packet* uni, char i);


void build_packet(uint8_t* snd , data_packet* uni);

void filter_lowpass(void);

void read_moving_speed(char id);

	

