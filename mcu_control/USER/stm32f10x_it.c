/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "delay.h"
#include "my_lib.h"
//#include "usart.h"

#define pulse_per_rev 4


 
int cnt = 0,delta_cnt;
extern  int speed;


extern u8 Encoder_res[10];
_Bool res_begin = 0;
int k = 0;
int i = 1;

extern double pos_tar;
extern double pos;
double pos_err;
extern int rotate_time;

void TIM4_IRQHandler(void)  //
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  
		{
			//rotate
			if(rotate_time>0) {TIM_SetCompare1(TIM3,750);rotate_time --;}
			else TIM_SetCompare1(TIM3,0);
			pos_err = __fabs(pos_tar-pos);
			delta_cnt = TIM2->CNT  - cnt;
			cnt = TIM2->CNT;
			if(delta_cnt>0) speed = (delta_cnt / TIMER_PERIOD) / pulse_per_rev * 60;
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  
		}
}

void USART2_IRQHandler(void)                	//串口2中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res =USART_ReceiveData(USART2);	//读取接收到的数据
		Encoder_res[i++] = Res;
		if(Res == 0xCD)//帧头 
					if(Encoder_res[i-2]==0xAB)
						i = 1;
  } 
}


void USART1_IRQHandler(void)                	//串口2中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{ 
  } 
}

void EXTI2_IRQHandler(void)
{

	EXTI_ClearITPendingBit(EXTI_Line2);
}
 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
