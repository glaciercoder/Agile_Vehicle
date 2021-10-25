#ifndef LED_H_
#define LED_H_
#include "stm32f10x.h"
typedef enum{red,blue,green} color;
void LED_Init(void);
uint16_t power(int n);
void setLED(color c, int n,int open);
void lEDSet(color c, int x,int y,int open);
void silienceall(void);

#endif

