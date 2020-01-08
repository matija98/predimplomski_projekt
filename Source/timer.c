#include <timer.h>

void timer5_init(void)
{
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
uint16_t TimerPeriod;
RCC_ClocksTypeDef RCC_Clocks;
uint32_t APB1_CLK;

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
TIM_ITConfig(TIM5, TIM_IT_Update, DISABLE);
RCC_GetClocksFreq(&RCC_Clocks);
APB1_CLK = RCC_Clocks.PCLK1_Frequency;
TimerPeriod = (uint16_t)((APB1_CLK * 2)/ 10000);
	
// Time Base configuration
TIM_TimeBaseStructure.TIM_Prescaler = 500 - 1;
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // counts from 0 to autoreload, and then back to 0
TIM_TimeBaseStructure.TIM_Period = TimerPeriod * FAKTOR - 1;
TIM_TimeBaseStructure.TIM_ClockDivision = 0;
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
// set TIM5 IRQ
TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

// Enable the TIM2 global Interrupt
NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

// TIM5 counter enable
TIM_Cmd(TIM5, ENABLE);
}


void TIM5_IRQHandler(void)
{
if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
        GPIO_ToggleBits(GPIOB, GPIO_Pin_3);
				GPIO_ToggleBits(GPIOG, GPIO_Pin_14);
    }
}
