#include "motor.h"
int integral_err = 0;
int pre_err = 0;
extern int speed;
extern float output;
	
void Motorinit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
 //PWM frequency =  72M/(arr+1)*(psc+1) 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = 899; 
	TIM_TimeBaseStructure.TIM_Prescaler =0; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);


	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	//正反转控制引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Pin = DR_REV;
	GPIO_Init(GPIOA, &GPIO_InitStructure);		
}

//Set TIM2 As encoder mode to calculate the speed of the driving motor
void Encoder_Init(void)//TIM2 PA1
{
	RCC->APB1ENR|=1<<0; //TIM2???? 
	RCC->APB2ENR|=1<<2; //??PORTA??

	GPIOA->CRL &= 0XFFFFFF0F; //
	GPIOA->CRL |= 0X00000080; //PA1????
	GPIOA->ODR |= 0<<1;

	TIM2->ARR=8999; //?????????? 
	TIM2->PSC=0; //???????

	TIM2->CCMR1|=1<<8; //CC2S=01 ????? IC1???TI2?
	TIM2->CCMR1|=0<<12; //IC2F=0000 ??????? ?Fck_int??
	TIM2->CCMR1|=0<<10; //IC2PS=00 ??????,???

	TIM2->CCER |=0<<5; //CC2P=0 ?????
	TIM2->SMCR |=0X07<<0; //SMS =111 
	TIM2->SMCR |=0X06<<4;  

	TIM2->CR1 |= 0x01; 
}

void SetDir(dir dir_)//rev/min
{
	if(dir_ == forward)
			GPIO_SetBits(GPIOA,DR_REV);		//C
	else
		GPIO_ResetBits(GPIOA,DR_REV);		//C
}


void PID_control(int tar)
{
	 int err;
	 err = tar - speed;
	 integral_err += err;
	 output = err*K_p + output + K_i*integral_err + K_d*(err- pre_err);
	 pre_err = err;
	 if(output<0)
		 output = 0;
	 else if(output>800)
		 output = 800;
	 TIM_SetCompare2(TIM3,(int)output+200);
}

