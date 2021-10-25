#include "exti.h"
#include "my_lib.h"
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTIStr;
	NVIC_InitTypeDef NVICStr;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	gpio_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_2,GPIO_Mode_IPD);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
	EXTIStr.EXTI_Line = EXTI_Line2;
	EXTIStr.EXTI_LineCmd = ENABLE;
	EXTIStr.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTIStr.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTIStr);
	
	NVICStr.NVIC_IRQChannel = EXTI2_IRQn;
	NVICStr.NVIC_IRQChannelCmd = ENABLE;
	NVICStr.NVIC_IRQChannelPreemptionPriority = 1;
	NVICStr.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVICStr);
}



