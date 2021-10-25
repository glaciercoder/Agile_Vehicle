#include "stepper.h"
#include "usart.h"

int t2_number;
extern int cnt;
extern double pos;
extern double pos_tar;
extern double pos_err;

void Stepperinit(void)//TIM3 CH1
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  
	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 //TIM3 will be init in motor.c
//   //初始化TIM3
//	TIM_TimeBaseStructure.TIM_Period = 19999;  
//	TIM_TimeBaseStructure.TIM_Prescaler =99; 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
//	
//	//初始化TIM3 Channel2 PWM模式	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
//	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
//  TIM_OC1Init(TIM3, &TIM_OCInitStructure);


//	TIM_Cmd(TIM3, ENABLE);  //使能TIM3		

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Pin = REV_PIN ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//reverse control
}



void Encoder_Init_Stepper(void)//USART2
{
	//GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;//I/O?ú3?ê??ˉ?á11ì?
    NVIC_InitTypeDef NVIC_InitStructure;//?D??3?ê??ˉ?á11ì?
    USART_InitTypeDef USART_InitStructure;//′??ú3?ê??ˉ?á11ì?  
    
    /* Enable the USART2 Pins Software Remapping */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB2Periph_AFIO, ENABLE);
    
    /* Configure USART2 Rx (PA.03) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure USART2 Tx (PA.02) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    USART_InitStructure.USART_BaudRate = 19200;                
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;     
    USART_InitStructure.USART_Parity = USART_Parity_No;        
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      
    
    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    /* Enable USART2 */
    USART_Cmd(USART2, ENABLE);
}




void setangle(float tar)
{
	pos_tar = tar;
	printf("setange started\n");	
	printf("pos = %lf  tar = %lf		",pos,pos_tar);
	if(pos_err<3)
			TIM_SetCompare1(TIM3,0);
	else
		TIM_SetCompare1(TIM3,750);
}

//void TIM4_IRQHandler(void)   //TIM4中断
//{
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
//		{
//			pos_err = __fabs(pos_tar-pos);
//			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx更新中断标志 
//		}
//}


int setangle_open(float delta_tar)//open loop control delta_tar for the change of tar
{
	//use 25000 oul/rev, 1152 degrees per second
	int d_second = 1152;
	int f_TIM4 = 10000;
	int rotate_time = delta_tar / d_second * f_TIM4;
	if(rotate_time >= 0) GPIO_SetBits(GPIOA,GPIO_Pin_0);
	else {GPIO_ResetBits(GPIOA,GPIO_Pin_0); rotate_time = -rotate_time;}
	return rotate_time;
}
double stepper_Decode(u8 Encoder_res[10])
{
	uint16_t x = (((uint16_t)Encoder_res[2]) << 8) | ((uint16_t)Encoder_res[3]);
	return ((double) x) / 1023.0 * 360.0;
}