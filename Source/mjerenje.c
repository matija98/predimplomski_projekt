#include <mjerenje.h>

uint32_t ReadValue1 = 0;
uint32_t ReadValue2 = 0;
uint16_t CaptureNumber = 0;
uint32_t Capture = 0;
double freq_interrupt = 0;
RCC_ClocksTypeDef RCC_Clocks_mjerenje;
uint32_t APB1_CLK;

void mjerenje_init(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  
	// Enable GPIOA clock
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  // Enable SYSCFG clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  // Configure PA0 pin as input
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Connect EXTI Line0 to PA0 pin
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  // Configure EXTI Line0
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  // Enable and set EXTI Line0 Interrupt to the highest priority
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
	RCC_GetClocksFreq(&RCC_Clocks_mjerenje);
	APB1_CLK = RCC_Clocks_mjerenje.PCLK1_Frequency;
  
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    if(CaptureNumber == 0)
    {
      // Get the Counter value 
      ReadValue1 = TIM_GetCounter(TIM2);
      CaptureNumber = 1;
    }
    else if(CaptureNumber == 1)
    {
      // Get the Counter value 
      ReadValue2 = TIM_GetCounter(TIM2); 
      
      // Counter computation 
      if (ReadValue2 > ReadValue1)
      {
        Capture = (ReadValue2 - ReadValue1); 
      }
      else if (ReadValue2 < ReadValue1)
      {
        Capture = ((0xFFFFFFFF - ReadValue1) + ReadValue2); 
      }
      else
      {
        Capture = 0;
      }
      // Frequency computation
      if (Capture != 0) freq_interrupt = (double)(APB1_CLK*2/100) / Capture;
			CaptureNumber = 0;
    }
		
    // Clear the EXTI line 0 pending bit
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}


void timer2_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// Time Base configuration
	TIM_TimeBaseStructure.TIM_Prescaler = 100 - 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // counts from 0 to autoreload, and then back to 0
	TIM_TimeBaseStructure.TIM_Period = 0xffffffff;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// TIM2 counter enable
	TIM_Cmd(TIM2, ENABLE);
}
