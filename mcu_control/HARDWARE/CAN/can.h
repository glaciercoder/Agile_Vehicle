#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
 //////////////////////////////////////////////////////////////////////////////////	 


//CAN����RX0�ж�ʹ��
#define CAN_RX0_INT_ENABLE	0		//0,��ʹ��;1,ʹ��.
//MAX value from host, this must be changed with host simultanously
#define ANG_MAX  3600
#define THR_AMX  1000

struct CAN_Info
{
	int16_t throttle;//driving motor speed
	int16_t degree;//degree of the stepper motor
	int frame_id;//frame id from the CAN
};

u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
 
u8 Can_Send_Msg(u8* msg,u8 len);						//��������

u8 Can_Receive_Msg(u8 *buf);							//��������

struct CAN_Info* CAN_Decode(uint8_t *CAN_Res,struct CAN_Info * CAN_info); 

#endif

















