#include "timer.h"
#include "usart.h"

//void TIM4_Int_Init(u16 arr,u16 psc)
//{
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

//	TIM_TimeBaseStructure.TIM_Period = arr; 
//	TIM_TimeBaseStructure.TIM_Prescaler =psc;  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
// 
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 

//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
//	NVIC_Init(&NVIC_InitStructure);  

//	TIM_Cmd(TIM4, ENABLE);  							 
//}






