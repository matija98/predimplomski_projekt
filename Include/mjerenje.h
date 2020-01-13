#ifndef MJERENJE_H
#define MJERENJE_H
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>

void mjerenje_init(void);
void EXTI0_IRQHandler(void);
void timer2_init(void);
extern double freq_interrupt;

#endif
