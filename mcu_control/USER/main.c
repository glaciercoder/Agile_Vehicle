#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "motor.h"
#include "can.h"
#include "sys.h"
#include "stepper.h"
//u16 val;

//Stepper Motor var
double pos = 0;//The postition of the stepper motor(degree)
double pos_tar = 0;//The target position of the stepper motor
u8 Encoder_res[9] = {0};
int rotate_time ;
//increment time used in open-loop control
int last_deg = 0;
int deg = 0;
int tar_degree = 0;

//CAN var
extern _Bool res_begin;
u8 CAN_Res[8] = {0};
u8 CAN_Buff[8] = {0,1,2,3,4,5,6,7};
struct CAN_Info CAN_info;
//Driving Motor var
int speed,tar_speed;//rev/min
float output;





int main()
{
//	u8 canbuf[8] = {1,2,3,4,5,6,7,8};
//define temp vars
int i = 0;	
	

/**************Init all hardwares***********
	*****************************************
	*****************************************/
 	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 
	Stepperinit();TIM_SetCompare1(TIM3,0);
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,2,CAN_Mode_Normal);//CAN初始化波特率1Mbps
	Encoder_Init_Stepper();
	TIM4_Int_Init(7199,0);//10Khz 
	TIM_Cmd(TIM4, ENABLE);
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 //used to communicate with the PC
	Motorinit();  TIM_SetCompare2(TIM3,0);
	Encoder_Init();

	Can_Send_Msg(CAN_Buff,8);
	
	while(1)
	{
		Can_Receive_Msg(CAN_Res);
		CAN_Decode(CAN_Res,&CAN_info);
		tar_speed = CAN_info.throttle / 2;
		deg = CAN_info.degree / 10;
		tar_degree = deg - last_deg;
		last_deg = deg;
		rotate_time = setangle_open(tar_degree);
		TIM_SetCompare2(TIM3,tar_speed+300);
		printf("Throttle:%d   ANG:%d",CAN_info.throttle,CAN_info.degree);
		printf("\r\n");
		delay_ms(100);
		
//		tar_speed = 625;
//		output = 400;
//		SetDir(forward);
//		TIM_SetCompare2(TIM3,0);
//		delay_ms(50);
	
//		while(1)
//		{
//			

//	////		Can_Send_Msg(canbuf,8);
//	//		setangle(10);
//	//		if(k % 2) GPIO_SetBits(GPIOA,GPIO_Pin_0);
//	//		else GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//	////		for(i = 0 ;i < 8;i++)
//	////			printf("%d ",canbuf[i]);
//	//		k++;

//	//		printf("%d      ",pos);
//			//TIM_SetCompare1(TIM3,0);

//			//printf("\r\n");
//			
//			
//			pos_tar = 90.0;
//			setangle();
//			PID_control(tar_speed);
//			printf("speed:%d	tar_speed:%d	pos:%lf	tar_pos:%lf\r\n",speed,tar_speed,pos,pos_tar);
//			if(__fabs(pos-pos_tar)<3)
//			{
//				printf("target position arrived!!!!\r\n");
//				break;
//			}

//			delay_ms(20);
//		}
		
//		TIM_SetCompare2(TIM3,0);
//		TIM_SetCompare1(TIM3,0);
//		delay_ms(1000);
////		delay_ms(1000);
//		
//		tar_speed = 625;
//		output = 400;
//		SetDir(backward);
//		TIM_SetCompare2(TIM3,0);
//		delay_ms(50);
		
		


//		TIM_SetCompare2(TIM3,0);
//		TIM_SetCompare1(TIM3,0);
//		delay_ms(1000);
//		delay_ms(1000);





/**********************Serial Debug***************************
*************************************************************/
//Very important to ensure the work of the serial port
//printf("Hello");



/*****************StepperMotor debug***************************
****************************************************************/
/*using 750 and all resolution button up, the stepper will work happily*/
/**Once open loop is finished, you can not just give a pwm to make it rotate**/
//get pos from RS485 USART2
//	GPIO_SetBits(GPIOA,GPIO_Pin_0);//REV
//TIM_SetCompare1(TIM3,0);
//TIM_SetCompare1(TIM3,750);
			//pos = stepper_Decode(Encoder_res);
			//for(int i = 2;i <= 5;i++) printf("%02x ",Encoder_res[i]);
			//printf("%f          ",pos);
			//delay_ms(500);
//Back and forward
//GPIO_SetBits(GPIOA,GPIO_Pin_0);
//delay_ms(2000);
//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//delay_ms(2000);
//open loop 
//360 degrees at a time
//rotate_time = setangle_open(180);
//delay_ms(800);
//rotate_time = setangle_open(-90);
//delay_ms(600);

/***************Driving Motor debug*******************************
******************************************************************/
//	TIM_SetCompare2(TIM3,400);//Rotate at a constant speed
//	tar_speed = 160;
//	PID_control(tar_speed);
//		delay_ms(5000);
//	tar_speed=320;
//	PID_control(tar_speed);
//	delay_ms(5000);
//		printf("speed:%d	tar_speed:%d	\r\n",speed,tar_speed);
//	 	delay_ms(500);


/********************CAN debug*************************************
*******************************************************************/
//		Can_Receive_Msg(CAN_Res);
//		CAN_Decode(CAN_Res,&CAN_info);
////	  for(i = 0;i < 8;i++)
////			printf("%c",CAN_Res[i]);
//printf("Throttle:%d   ANG:%d",CAN_info.throttle,CAN_info.degree);
//		printf("\r\n");
//		delay_ms(100);
//		Can_Send_Msg(CAN_Buff,8);
//		delay_ms(100);
	}
	return 0;
}
