/**
  ******************************************************************************
  * @author  Matija Purgar
  * @date    09-12-2019
  * @brief   Preddiplomski projekt mjerenja pseudo pulsa i ispisa na ekran

**/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
  
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

/* Private functions ---------------------------------------------------------*/
int calc_pulse(double freq);
void print_on_screen(int pulse_value);


/* Main program */
int main(void)
{
	double freq = 0;
	int puls = 0;

	// SysTick end of count event each 10ms
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
  
  // Inicijalizacija LCDa
  LCD_Init();
	LCD_LayerInit();
  LTDC_Cmd(ENABLE);
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
  LCD_Clear(LCD_COLOR_WHITE);
  
	// Inicijalizacija LED4 i PB03
	gpio_init();
	
	// Inicijalizacija timera koji generira 
	// pravokutni signal prekidom
	timer5_init();
	
	// Inicijalizacija timera pomocu kojega 
	// ocitavamo vrijeme za racunanje frekvencije
	timer2_init();
	
	// Inicijalizacija vanjskog prekida
	mjerenje_init();
	
	
  while (1)
	{
		// Dohvati frekvenciju
		freq = uwTIM1Freq;
		
		// Izracunaj puls
		puls = calc_pulse(freq);
		
		// Ispisi puls
		print_on_screen(puls);
	}
}


// Racunanje pulsa iz frekvencije signala
int calc_pulse(double freq)
{
	return (int)((60*freq)+0.5);
}

// Ispis pulsa na ekran
void print_on_screen(int pulse_value)
{
	char zap[12]={0};
	
	sprintf(zap, "%d", pulse_value);
	strcat(zap, " bpm");
	
	if ((pulse_value >= 40) && (pulse_value <= 120))
	{
		// Dobar puls
		LCD_Clear(LCD_COLOR_WHITE);
    LCD_SetTextColor(LCD_COLOR_GREEN);
		LCD_DisplayStringLine(80, "Puls je:");
		LCD_DisplayStringLine(140, zap);
		Delay(50);
	}
	else
	{
		// Los puls
		LCD_Clear(LCD_COLOR_WHITE);
   	LCD_SetTextColor(LCD_COLOR_RED);
		LCD_DisplayStringLine(80, "Puls je:");
		LCD_DisplayStringLine(140, zap);
		Delay(50);
	}
}


/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
