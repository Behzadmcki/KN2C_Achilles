#include "main.h"
#include "mpu6050.h"


MPU_SENSOR Mpu;
MPU_SENSOR Mpu_ODO;
ch2int _con;
uint8_t teemp=0;

void Mpu_Write(MPU_SENSOR *sen,char Reg,char data)
{
	HAL_I2C_Mem_Write(&sen->I2C,sen->Add,Reg,1,(uint8_t *)&data,1,1000);
}

char  Mpu_Read(MPU_SENSOR *sen,char Reg)
{
	char data;
	teemp=HAL_I2C_Mem_Read(&sen->I2C,sen->Add,Reg,1,(uint8_t *)&data,1,1000);
	return data;
}

void init_mpu(MPU_SENSOR *sen,I2C_HandleTypeDef *hi2cx , int address , int calib)
{
	sen->I2C = *hi2cx;
	sen->Add = address;
	
	Mpu_Write(sen,MPUREG_PWR_MGMT_1,0x80);
	HAL_Delay(5);
	
	Mpu_Write(sen,MPUREG_SMPLRT_DIV,0x00);
	HAL_Delay(5);
	
	Mpu_Write(sen,MPUREG_PWR_MGMT_1,0x03); 
	HAL_Delay(5);
	
	Mpu_Write(sen,MPUREG_GYRO_CONFIG,BITS_FS_2000DPS); 
	HAL_Delay(5);
	
	Mpu_Write(sen,MPUREG_USER_CTRL,0x00); 
	HAL_Delay(5);
	
	Mpu_Write(sen,MPUREG_INT_PIN_CFG,0x02); 
	HAL_Delay(5);
	
	Mpu_Write(sen,MPUREG_CONFIG, BITS_DLPF_CFG_20HZ); 
	HAL_Delay(5);
	
	Mpu_Write(sen,MPUREG_ACCEL_CONFIG,0x18);  // Accel scale 16g (2048LSB/g) 
	HAL_Delay(5);
	
	gyro_calib(sen,calib);
	
//	sen->gyrox_offset = EEPROM_Read_int16_t(EEPROM_GYRO_Offset_X);
//	sen->gyroy_offset = EEPROM_Read_int16_t(EEPROM_GYRO_Offset_Y);
//	sen->gyroz_offset = EEPROM_Read_int16_t(EEPROM_GYRO_Offset_Z);

//	sen->Gravity  = EEPROM_Read_int16_t(EEPROM_GRAVITY);
	
//	print2pc("Mpu:%d,%d",Mpu_Read(sen,MPUREG_GYRO_CONFIG),Mpu_Read(sen,MPUREG_CONFIG));
	
}


char  ping_mpu(MPU_SENSOR *sen)
{
	char data=0;
	HAL_I2C_Mem_Read(&sen->I2C,sen->Add,MPUREG_WHOAMI,1,(uint8_t *)&data,1,1000);
	return data;
}



void Mpu_Read_acc(MPU_SENSOR *sen)
{
	
	_con.byte[1] = Mpu_Read(sen , MPUREG_ACCEL_XOUT_H);
	_con.byte[0] = Mpu_Read(sen , MPUREG_ACCEL_XOUT_L);
	sen->acc_x =  _con.real;
	
	_con.byte[1] = Mpu_Read(sen , MPUREG_ACCEL_YOUT_H);
	_con.byte[0] = Mpu_Read(sen , MPUREG_ACCEL_YOUT_L);
	sen->acc_y = _con.real;
	
	_con.byte[1] = Mpu_Read(sen , MPUREG_ACCEL_ZOUT_H);
	_con.byte[0] = Mpu_Read(sen , MPUREG_ACCEL_ZOUT_L);
	sen->acc_z = _con.real;
	
	 
	sen->acc_x=sen->last_acc_x+ (DT / ( FILTER_ACC + DT)) * (sen->acc_x - sen->last_acc_x);
	sen->acc_y=sen->last_acc_y+ (DT / ( FILTER_ACC + DT)) * (sen->acc_y - sen->last_acc_y);
	sen->acc_z=sen->last_acc_z+ (DT / ( FILTER_ACC + DT)) * (sen->acc_z - sen->last_acc_z);
	
	sen->last_acc_x =sen->acc_x;
	sen->last_acc_y =sen->acc_y;
	sen->last_acc_z =sen->acc_z;
	
}

void Mpu_Read_gyro(MPU_SENSOR *sen)
{
	
	_con.byte[1] = Mpu_Read(sen , MPUREG_GYRO_XOUT_H);
	_con.byte[0] = Mpu_Read(sen , MPUREG_GYRO_XOUT_L);
	sen->gyro_x_real =  _con.real;
	
	_con.byte[1] = Mpu_Read(sen , MPUREG_GYRO_YOUT_H);
	_con.byte[0] = Mpu_Read(sen , MPUREG_GYRO_YOUT_L);
	sen->gyro_y_real =  _con.real;
	
	_con.byte[1] = Mpu_Read(sen , MPUREG_GYRO_ZOUT_H);
	_con.byte[0] = Mpu_Read(sen , MPUREG_GYRO_ZOUT_L);
	sen->gyro_z_real =  _con.real;
	
	sen->gyro_x_real = sen->gyro_x_real - sen->gyrox_offset;
	sen->gyro_y_real = sen->gyro_y_real - sen->gyroy_offset;
	sen->gyro_z_real = sen->gyro_z_real - sen->gyroz_offset;
	
  sen->gyro_x_real = (fabs(sen->gyro_x_real)> GyroThreshold) ? sen->gyro_x_real  : 0;
	sen->gyro_y_real = (fabs(sen->gyro_y_real)> GyroThreshold) ? sen->gyro_y_real  : 0;
	sen->gyro_z_real = (fabs(sen->gyro_z_real)> GyroThreshold) ? sen->gyro_z_real  : 0;
	
	sen->gyro_x = Gyro_Scaled_X(sen->gyro_x_real);
	sen->gyro_y = Gyro_Scaled_Y(sen->gyro_y_real);
	sen->gyro_z = Gyro_Scaled_Z(sen->gyro_z_real);
}


void Mpu_update(MPU_SENSOR *sen)
{
	Mpu_Read_acc(sen);
	Mpu_Read_gyro(sen);
	Update_Gravity(sen);
}


void gyro_calib(MPU_SENSOR *sen,char permision)
{
    float  GX_ave, GY_ave, GZ_ave;
    int i=0;
	
    if(permision==1)
    {     
//				print2pcs("start gyro calib \r");
        HAL_Delay(1000); 
        sen->gyrox_offset=0;           
        sen->gyroy_offset=0;    
        sen->gyroz_offset=0;    
                   
        for(i=0;i<100;i++)
        {
            Mpu_Read_gyro(sen);
            
            GX_ave=GX_ave+sen->gyro_x_real;
            GY_ave=GY_ave+sen->gyro_y_real;
            GZ_ave=GZ_ave+sen->gyro_z_real;
					
//						print2pc("Gyro = %d,%d,%d\r",(int)sen->gyro_x_real,(int)sen->gyro_y_real,(int)sen->gyro_z_real);
        }      
        GX_ave/=100;
        GY_ave/=100;
        GZ_ave/=100;
                 
        sen->gyrox_offset=(int)GX_ave;     
        sen->gyroy_offset=(int)GY_ave;     
        sen->gyroz_offset=(int)GZ_ave;  

//				print2pc("Gyro_offset = %d,%d,%d \r",(int)sen->gyrox_offset,(int)sen->gyroy_offset,(int)sen->gyroz_offset);
            
         
        
				
//				EEPROM_Write_int16_t(EEPROM_GYRO_Offset_X,(int16_t)sen->gyrox_offset);
//        EEPROM_Write_int16_t(EEPROM_GYRO_Offset_Y,(int16_t)sen->gyroy_offset);
//				EEPROM_Write_int16_t(EEPROM_GYRO_Offset_Z,(int16_t)sen->gyroz_offset);
				
				HAL_Delay(1000);
    }    
}



void Update_Gravity(MPU_SENSOR *sen)
{
    
    sen->Accel_magnitude = sqrt(sen->acc_x*sen->acc_x + sen->acc_y * sen->acc_y + sen->acc_z * sen->acc_z);
  
    sen->Accel_magnitude_hpf = (FILTER_GRAVITY_hpf / (FILTER_GRAVITY_hpf + DT)) * (sen->Accel_magnitude - sen->last_Accel_magnitude + sen->last_Accel_magnitude_hpf );
    
    sen->last_Accel_magnitude_hpf = sen->Accel_magnitude_hpf;
    sen->last_Accel_magnitude = sen->Accel_magnitude;    
    
    if(fabs(sen->Accel_magnitude_hpf) < 4)
    {
        sen->Gravity = sen->Gravity +(DT / ( FILTER_GRAVITY_lpf + DT)) * (sen->Accel_magnitude - sen->Gravity);    
    }
    
    
    sen->Accel_magnitude = sen->Accel_magnitude / sen->Gravity;
    sen->g_print=fabs(fabs(1.0f-sen->Accel_magnitude ));    
    sen->g_print= sen->g_print; 

}




