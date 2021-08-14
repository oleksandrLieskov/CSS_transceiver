#include "main.h"

void digiPotGPIO_Init(void)
{
	// Clock ON port B!!!!!!!!!
	/* CS */
	GPIOB->CRL |= GPIO_CRL_MODE5_1 & ~(GPIO_CRL_MODE5_0);   // Output Push-Pull pin B5, Speed 2 MHz
	GPIOB->CRL &= ~(GPIO_CRL_CNF5_1) & ~(GPIO_CRL_CNF5_0);
	GPIOB->BSRR |= GPIO_BSRR_BS5;                           // Output high level on pin B5
	/* INC */
	GPIOB->CRL |= GPIO_CRL_MODE6_1 & ~(GPIO_CRL_MODE6_0);   // Output Push-Pull pin B6, Speed 2 MHz
	GPIOB->CRL &= ~(GPIO_CRL_CNF6_1) & ~(GPIO_CRL_CNF6_0);
	/* U/D */
	GPIOB->CRL |= GPIO_CRL_MODE7_1 & ~(GPIO_CRL_MODE7_0);   // Output Push-Pull pin B7, Speed 2 MHz
	GPIOB->CRL &= ~(GPIO_CRL_CNF7_1) & ~(GPIO_CRL_CNF7_0);
}

void digiPot_AdjustToZero(void)
{
	GPIOB->BSRR |= GPIO_BSRR_BR5;    // Output high level on pin B5
	GPIOB->BSRR |= GPIO_BSRR_BR7;    // Output high level on pin B7
	for(int i = 0; i < 100; i++)
	{
		GPIOB->BSRR |= GPIO_BSRR_BS6;
		GPIOB->BSRR |= GPIO_BSRR_BR6;
	}
	GPIOB->BSRR |= GPIO_BSRR_BS6;
	GPIOB->BSRR |= GPIO_BSRR_BS5;
}

void digiPot_SetRes(int16_t resValue)
{
	int r = abs(resValue) / MINIMUM_INCREMENT;
	if(abs(resValue) % MINIMUM_INCREMENT > 50)
	{
		r++;
	}
	GPIOB->BSRR |= GPIO_BSRR_BR5;
	if(resValue > 0)
	{
		GPIOB->BSRR |= GPIO_BSRR_BS7;
	}
	else
	{
		GPIOB->BSRR |= GPIO_BSRR_BR7;
	}
	for(int i = 0; i < r; i++)
	{
		GPIOB->BSRR |= GPIO_BSRR_BS6;
		GPIOB->BSRR |= GPIO_BSRR_BR6;
	}
	GPIOB->BSRR |= GPIO_BSRR_BS6;
	GPIOB->BSRR |= GPIO_BSRR_BS5;
}
