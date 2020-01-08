#ifndef MJERENJE_H
#define MJERENJE_H
#include <stm32f4xx.h> // common stuff
#include <stm32f4xx_gpio.h> // gpio control
#include <stm32f4xx_rcc.h> // reset anc clocking
#include <stm32f4xx_tim.h> // timers

void mjerenje_init(void);
void EXTI0_IRQHandler(void);
void timer2_init(void);
extern double freq_interrupt;

#endif
