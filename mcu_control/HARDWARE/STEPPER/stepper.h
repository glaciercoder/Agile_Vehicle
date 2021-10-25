#ifndef STEPPER_H_
#define STEPPER_H_
#include "stm32f10x.h"


#define REV_PIN GPIO_Pin_0  //forward and reverse control, Port A


#define UP_DOWN_NUMBER 36
void Stepperinit(void);
void Encoder_Init_Stepper(void);
void setangle(float tar);
double stepper_Decode(u8 Encoder_res[10]);
int setangle_open(float delta_tar);


#endif

