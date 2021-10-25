#include "LED.h"

#include "my_lib.h"
void LED_Init(void)
{
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_0,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_1,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_2,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_3,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_4,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_5,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_6,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_7,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_8,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_9,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_10,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_11,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_12,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_13,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_14,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOA,GPIOA,GPIO_Pin_15,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_13, GPIO_Mode_Out_PP);  
  gpio_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_14, GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_0,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_1,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_2,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_3,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_4,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_5,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_6,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_7,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_8,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_10,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_11,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_12,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_13,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_14,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOB,GPIOB,GPIO_Pin_15,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_4,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_5,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_10,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_11,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_12,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_8,GPIO_Mode_Out_PP);
	gpio_init(RCC_APB2Periph_GPIOC,GPIOC,GPIO_Pin_9,GPIO_Mode_Out_PP);
}

uint16_t power(int n)
{
	uint16_t temp = 1;
	if(n)
		temp =temp<< n;
	return temp;
}


void setLED(color c, int n,int open)
{
	switch(c)
	{
		case blue: switch(n)
		{
			case 1:if(open) {GPIO_SetBits(GPIOA,GPIO_Pin_0);GPIO_ResetBits(GPIOA,GPIO_Pin_8);}
							else GPIO_ResetBits(GPIOA,GPIO_Pin_0);break;
			case 2:if(open) GPIO_SetBits(GPIOA,GPIO_Pin_1);
							else GPIO_ResetBits(GPIOA,GPIO_Pin_1);break;
			case 3:if(open) GPIO_SetBits(GPIOA,GPIO_Pin_2);
							else GPIO_ResetBits(GPIOA,GPIO_Pin_2);break;
			case 4:if(open) GPIO_SetBits(GPIOA,GPIO_Pin_3);
							else GPIO_ResetBits(GPIOA,GPIO_Pin_3);break;
			case 5:if(open) GPIO_SetBits(GPIOA,GPIO_Pin_4);
					else GPIO_ResetBits(GPIOA,GPIO_Pin_4);break;
			case 6:if(open) GPIO_SetBits(GPIOA,GPIO_Pin_5);
							else GPIO_ResetBits(GPIOA,GPIO_Pin_5);break;
			case 7:if(open) GPIO_SetBits(GPIOA,GPIO_Pin_6);
							else GPIO_ResetBits(GPIOA,GPIO_Pin_6);break;
			case 8:if(open) GPIO_SetBits(GPIOA,GPIO_Pin_7);
							else GPIO_ResetBits(GPIOA,GPIO_Pin_7);break;

		}
		break;
		default: break;
	}
}

void silienceall(void)
{
	int i = 1;
	for(i = 0;i<8;i++)
	{
		GPIO_ResetBits(GPIOA,power(i));
		GPIO_SetBits(GPIOB,power(i));
	}
	for(i =1;i<=8;i++)
	{
		GPIO_SetBits(GPIOA,power(7+i));
		GPIO_SetBits(GPIOB,power(7+i));
	}
	GPIO_SetBits(GPIOC,GPIO_Pin_11);
	GPIO_SetBits(GPIOC,GPIO_Pin_10);
	GPIO_SetBits(GPIOC,GPIO_Pin_12);
}
	





void lEDSet(color c, int x,int y,int open)//one at a time
{
	uint16_t i= 1;
	switch(c)
	{
		case blue: 
			if(open)
			{
				silienceall();
				if((y!= 7)&&(y!=6))
				{
					GPIO_SetBits(GPIOA,power(x-1));
					GPIO_ResetBits(GPIOA,power(7+y));
			  }
				else 
				{
					GPIO_SetBits(GPIOA,power(x-1));
					if(y==6)
					{
						GPIO_ResetBits(GPIOC,GPIO_Pin_10);
						GPIO_SetBits(GPIOC,GPIO_Pin_11);
					}
					else
					{
						GPIO_ResetBits(GPIOC,GPIO_Pin_11);
						GPIO_SetBits(GPIOC,GPIO_Pin_10);
					}
				}
		}
			else
			{
			  silienceall();
			}		
			break;
		case red:
			if(open)
			{
					silienceall();
				  GPIO_SetBits(GPIOA,power(x-1));
				if(y != 3)
					GPIO_ResetBits(GPIOB,power(y-1));
				else
					GPIO_ResetBits(GPIOC,GPIO_Pin_12);

			  }
			else
			{
				silienceall();
			}
			break;
		case green:
			if(open)
			{
				  silienceall();
					GPIO_SetBits(GPIOA,power(x-1));
					GPIO_ResetBits(GPIOB,power(7+y));
			  }
			else
			{
			  silienceall();
			}
			break;
			
	}
}


