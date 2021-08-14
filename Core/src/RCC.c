#include "main.h"
#include "RCC.h"


void RCC_Init(void)
{
	RCC->CR |= RCC_CR_HSEON;            // Start crystal generator
	while(!(RCC->CR & RCC_CR_HSERDY))   // Wait switched crystal generator
	{

	}

	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY; // Flash clock ON

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;  // AHB div
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // APB2 div
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1; // APB1 div

	RCC->CFGR |= RCC_CFGR_PLLSRC; // HSE source for PLL
	RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE;
	RCC->CFGR |= RCC_CFGR_PLLMULL9;
	RCC->CR   |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_HSERDY))   // Wait switched PLL
	{

	}
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1)
	{

	}
}
