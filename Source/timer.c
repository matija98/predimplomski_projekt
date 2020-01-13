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

/* Racunanje perioda, TIM5 radi po duploj frekvenciji APB1_CLK,
	 dijeljenje s 1000 za 1kHz, pa s 10 zbog FAKTORA */
TimerPeriod = (uint16_t)((APB1_CLK * 2) / 1000 / 10);  
// Konfiguracija brojila
TIM_TimeBaseStructure.TIM_Prescaler = 500 - 1; // Konacna frekvencija brojila se dijeli jos s 500, da dodemo na razinu od 1 Hz
TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // broji od 0 do ARR, pa ponovno na 0
TIM_TimeBaseStructure.TIM_Period = TimerPeriod * FAKTOR - 1; /* FAKTOR služi za brzu promjenu frekvencije, 
																																jednak 10 za generiranje 1 Hz */
TIM_TimeBaseStructure.TIM_ClockDivision = 0;
TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
// postavljanje TIM5 IRQ
TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

// Omogucavanje globalnog prekida TIM5
NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);

// Pokretanje brojila
TIM_Cmd(TIM5, ENABLE);
}

void TIM5_IRQHandler(void)
{
if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM5, TIM_IT_Update); // Resetiranje prekida
        GPIO_ToggleBits(GPIOB, GPIO_Pin_3); // Promjena stanja na PB03
				GPIO_ToggleBits(GPIOG, GPIO_Pin_14); // Promjena stanja na PG14 (LED4)
    }
}
