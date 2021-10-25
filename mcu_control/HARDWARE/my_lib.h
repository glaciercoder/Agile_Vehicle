#ifndef MYLIB_H_
#define MYLIB_H_
#include "stm32f10x.h"

  #define TIMER_PERIOD 0.3
#define ARR_TIMER 2999
#define PRE_SCALETIMER 7199  //0.5s for period
//0.5s

typedef enum {LOW = 0,HIGH = 1} digitaloutput;

void gpio_init(uint32_t  RCC_APB2Periph_GPIOX,GPIO_TypeDef* GPIOx, uint16_t GPIO_PinX,GPIOMode_TypeDef Mode);
void my_uart_init(u32 bound);
void extix_Init(void);   
void TIM4_Int_Init(u16 arr, u16 psc);
void TIM3_PWM_Init(u16 arr, u16 psc);



#endif
