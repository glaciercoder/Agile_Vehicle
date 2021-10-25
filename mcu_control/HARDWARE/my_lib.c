#include "my_lib.h"

void gpio_init(uint32_t  RCC_APB2Periph_GPIOX,GPIO_TypeDef* GPIOx, uint16_t GPIO_PinX,GPIOMode_TypeDef Mode)//����IO��
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOX,ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
 
 GPIO_InitStructure.GPIO_Pin = GPIO_PinX;				 
 GPIO_InitStructure.GPIO_Mode = Mode; 		 //ģʽ����
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ĭ��Ϊ50MHz
 GPIO_Init(GPIOx, &GPIO_InitStructure);						
		
	GPIO_ResetBits(GPIOx,GPIO_PinX);	
}

void my_uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
/* ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/	 
	
	
/*ȡ����stm32 ���ڸ�������  ��   ���޸�*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��,
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9,  
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
/* ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/	 


  //Usart1 NVIC ����
	/*��stm32f10x_it.c ������USART1_IRQHandler()����*/
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������
/*�Զ����֡��ʽ*/
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	//���������նˣ���������޸�Ϊ�����ж�
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
}


void extix_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4); //default GPIOE_Pin 4
	EXTI_InitTypeDef EXIT_InitStr;
	NVIC_InitTypeDef NVIC_InitStr;
	
	
	EXIT_InitStr.EXTI_Line = EXTI_Line4;  //default Line4
	EXIT_InitStr.EXTI_LineCmd = ENABLE;
	EXIT_InitStr.EXTI_Mode = EXTI_Mode_Interrupt;
	EXIT_InitStr.EXTI_Trigger= EXTI_Trigger_Falling; //default falling
	EXTI_Init(&EXIT_InitStr);
	
	NVIC_InitStr.NVIC_IRQChannel = EXTI4_IRQn;//��stm32f10x_it.c ������EXTI4_IRQHandler()����
	NVIC_InitStr.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStr.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStr.NVIC_IRQChannelSubPriority = 4;
	
	NVIC_Init(&NVIC_InitStr);
}


void TIM4_Int_Init(u16 arr, u16 psc)//��stm32f10x_it.c ������TIMx_IRQHandler()����
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStr;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//useless
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM4�ж�,��������ж�
	
	NVIC_InitStr.NVIC_IRQChannel = TIM4_IRQn;//
	NVIC_InitStr.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStr.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStr.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStr);
	
	TIM_Cmd(TIM4,ENABLE);
}

void TIM3_PWM_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStr;
	TIM_OCInitTypeDef TIM_OCInitStr;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitStr.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStr.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStr);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_OCInitStr.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStr.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStr.TIM_OCIdleState = TIM_OutputState_Enable;
	TIM_OC2Init(TIM3, &TIM_OCInitStr);
	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3,ENABLE);
}




