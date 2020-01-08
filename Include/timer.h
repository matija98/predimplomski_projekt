#ifndef TIMER_H
#define TIMER_H
#include <stm32f4xx.h> // common stuff
#include <stm32f4xx_gpio.h> // gpio control
#include <stm32f4xx_rcc.h> // reset anc clocking
#include <stm32f4xx_tim.h> // timers

void timer5_init(void);

#define FAKTOR 5	// 10 je za 1Hz, manje od toga je veca frekvencija
									// za 1 je 10Hz
									// za 5 je 2Hz
#endif
