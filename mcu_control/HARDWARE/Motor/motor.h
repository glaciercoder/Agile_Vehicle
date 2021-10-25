#ifndef MOTOR_H_
#define MOTOR_H_
#include "stm32f10x.h"


/*some information */ 
/*start up pwmlevel : 340   */

#define DR_REV GPIO_Pin_4 //forward and reverse control, Port A

#define K_p 1 //
#define K_i 0 //0.0006
#define K_d 0

typedef enum{forward,backward}dir;
void Motorinit(void);
void Encoder_Init(void);
void PID_control(int tar);
void SetDir(dir dir_);

#endif