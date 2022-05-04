#ifndef __Motor_HPP__
#define __Motor_HPP__

#include <variable.h>


struct FilterVar
{
	    float F_CUT;
	    float FILTER;
	    float DT;
	    float Last_PWM;
    	float Filtered_PWM;
	FilterVar()
	{
		
	}
	
	
};

class MOTOR
{
	private:
	
	public:
			

	    GPIO_TypeDef* GPIO_Port_ENA ;
			uint16_t GPIO_Pin_ENA ;
			
			GPIO_TypeDef* GPIO_Port_ENB ;
			uint16_t GPIO_Pin_ENB ;
			
			TIM_HandleTypeDef *timerType ;
			uint16_t timerChannel ;
	
	    int mainMotorInv;
			int motorMode;
	
	
	    
	    
	    int motorPWM;
	    int motorDirection;
    	int motorData[3];
	    int motorAD ;
				

	 
	    FilterVar PWMFilterVar;
	
			MOTOR();
			MOTOR(int _motorAD);


			void MotorStart(void);
			void static CheckConnection(void);
			void MotorData(void);
			void MotorMove(void);
			void MotorSetting(void);
			void SlaveSetting1(void);
			void SlaveSetting2(void);
			void SlaveSetting3(void);
			void SlaveSetting4(void);
			void PWMSetting(int settingType);
	    void MotorInv(int _globalDriverAD,int _motorAD);
			void FilterSetting(struct FilterVar *_filterVar,float _PWM_F_CUT,float _PWM_DT );
			void static MotorAction(void);
			void static MotorInit(void);


		void DoFilter(struct FilterVar *FilterVar);
};


extern MOTOR motor1;
extern MOTOR motor2;
extern MOTOR motor3;




#endif


