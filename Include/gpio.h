#ifndef GPIO_H
#define GPIO_H
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

#define IZLAZ_RCC RCC_AHB1Periph_GPIOB
#define IZLAZ_GPIOB GPIOB
#define IZLAZ_BROJ GPIO_Pin_3
#define LED4_RCC RCC_AHB1Periph_GPIOG
#define LED4_GPIOG GPIOG
#define LED4_BROJ GPIO_Pin_14


void gpio_init(void);

#endif
