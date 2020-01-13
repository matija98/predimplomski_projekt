#include <gpio.h>

void gpio_init()
{
// Konfiguracija pina PB03
GPIO_InitTypeDef GPIO_InitStruct;
RCC_AHB1PeriphClockCmd(IZLAZ_RCC, ENABLE);
GPIO_InitStruct.GPIO_Pin = IZLAZ_BROJ;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(IZLAZ_GPIOB, &GPIO_InitStruct);

// Konfiguracija LED4
RCC_AHB1PeriphClockCmd(LED4_RCC, ENABLE);
GPIO_InitStruct.GPIO_Pin = LED4_BROJ;
GPIO_Init(LED4_GPIOG, &GPIO_InitStruct);
}
