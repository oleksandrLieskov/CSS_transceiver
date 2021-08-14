#include "main.h"
#include "AD9850.h"


#ifdef _SERIAL_COMUNICATION_H

void AD9850_GPIO_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Clock port A ON
	/* W_CLK (A1) */
	GPIOA->CRL |= GPIO_CRL_MODE1_1 & ~(GPIO_CRL_MODE1_0);   // Output Push-Pull pin A9, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF1_1) & ~(GPIO_CRL_CNF1_0);

	/* FQ_UD (A2) */
	GPIOA->CRL |= GPIO_CRL_MODE2_1 & ~(GPIO_CRL_MODE2_0);  // Output Push-Pull pin A10, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF2_1) & ~(GPIO_CRL_CNF2_0);

	/* SerialData (A3) */
	GPIOA->CRL |= GPIO_CRL_MODE3_1 & ~(GPIO_CRL_MODE3_0);  // Output Push-Pull pin A11, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF3_1) & ~(GPIO_CRL_CNF3_0);

	/* RESET (A4) */
	GPIOA->CRL |= GPIO_CRL_MODE4_1 & ~(GPIO_CRL_MODE4_0);  // Output Push-Pull pin A12, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF4_1) & ~(GPIO_CRL_CNF4_0);

}
void AD9850_SerialStart(void)
{
	/* RESET Pulse */
	GPIOA->BSRR |= GPIO_BSRR_BS4;
	GPIOA->BSRR |= GPIO_BSRR_BR4;
	/* W_CLK Pulse */
	GPIOA->BSRR |= GPIO_BSRR_BS1;
	GPIOA->BSRR |= GPIO_BSRR_BR1;
	/* FQ_UD Pulse */
	GPIOA->BSRR |= GPIO_BSRR_BS2;
	GPIOA->BSRR |= GPIO_BSRR_BR2;
}
void AD9850_SerialTransiveByte(uint8_t byte)
{
	for(int i = 0; i < 8; i++, byte >>= 1)
	{
		if(byte & 0x01)
		{
			GPIOA->BSRR |= GPIO_BSRR_BS3;
		}
		else
		{
			GPIOA->BSRR |= GPIO_BSRR_BR3;
		}
		/* W_CLK Pulse */
		GPIOA->BSRR |= GPIO_BSRR_BS1;
		GPIOA->BSRR |= GPIO_BSRR_BR1;
	}
}
void AD9850_SerialSendFrequancy(double freq)
{
	uint32_t fout = (uint32_t)(freq * INT_MAX/FREQ_BASE_GENERATOR);
	for(int i = 0; i < 4; i++, fout >>= 8)
	{
		AD9850_SerialTransiveByte(fout & 0xff);
	}
	AD9850_SerialTransiveByte(0x00);
	/* FQ_UD Pulse */
	GPIOA->BSRR |= GPIO_BSRR_BS2;
	GPIOA->BSRR |= GPIO_BSRR_BR2;
}
void AD9850_CSS_SendString(uint8_t* comandBufer)
{
	uint8_t i = 0;
	while(comandBufer[i] != '\0')
	{
		AD9850_CSS_SendChar(comandBufer[i]);
		i++;
	}
	memset(comandBufer, 0, 19);
}
void AD9850_CSS_SendChar(uint8_t byte)
{
	for(int i = 0; i < 8; i++, byte >>= 1)
	{
		if(byte & 0x01)
		{
			AD9850_CSS_High();
		}
		else
		{
			AD9850_CSS_Low();
		}
	}
}
void AD9850_CSS_Low(void)
{
	float i = 10.0;
	AD9850_SerialSendFrequancy(i);
	while(i > 1.0)
	{
		i = i - 0.1;
		AD9850_SerialSendFrequancy(i);
		delay_mk(100000);
	}
}
void AD9850_CSS_High(void)
{
	float i = 1.0;
	AD9850_SerialSendFrequancy(i);
	while(i < 10.0)
	{
		i = i + 0.1;
		AD9850_SerialSendFrequancy(i);
		delay_mk(100000);
	}
}

#endif

#ifdef _PARALEL_COMUNICATION_H

void AD9850_GPIO_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Clock port A ON
	/* D0 */
	GPIOA->CRL |= GPIO_CRL_MODE0_1 & ~(GPIO_CRL_MODE0_0);   // Output Push-Pull pin A0, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF0_1) & ~(GPIO_CRL_CNF0_0);
	/* D1 */
	GPIOA->CRL |= GPIO_CRL_MODE1_1 & ~(GPIO_CRL_MODE1_0);   // Output Push-Pull pin A1, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF1_1) & ~(GPIO_CRL_CNF1_0);
	/* D2 */
	GPIOA->CRL |= GPIO_CRL_MODE2_1 & ~(GPIO_CRL_MODE2_0);   // Output Push-Pull pin A2, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF2_1) & ~(GPIO_CRL_CNF2_0);
	/* D3 */
	GPIOA->CRL |= GPIO_CRL_MODE3_1 & ~(GPIO_CRL_MODE3_0);   // Output Push-Pull pin A3, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF3_1) & ~(GPIO_CRL_CNF3_0);
	/* D4 */
	GPIOA->CRL |= GPIO_CRL_MODE4_1 & ~(GPIO_CRL_MODE4_0);   // Output Push-Pull pin A4, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF4_1) & ~(GPIO_CRL_CNF4_0);
	/* D5 */
	GPIOA->CRL |= GPIO_CRL_MODE5_1 & ~(GPIO_CRL_MODE5_0);   // Output Push-Pull pin A5, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF5_1) & ~(GPIO_CRL_CNF5_0);
	/* D6 */
	GPIOA->CRL |= GPIO_CRL_MODE6_1 & ~(GPIO_CRL_MODE6_0);   // Output Push-Pull pin A6, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF6_1) & ~(GPIO_CRL_CNF6_0);
	/* D7 */
	GPIOA->CRL |= GPIO_CRL_MODE7_1 & ~(GPIO_CRL_MODE7_0);   // Output Push-Pull pin A7, Speed 2 MHz
	GPIOA->CRL &= ~(GPIO_CRL_CNF7_1) & ~(GPIO_CRL_CNF7_0);
	/* W_CLK (A9) */
	GPIOA->CRH |= GPIO_CRH_MODE9_1 & ~(GPIO_CRH_MODE9_0);   // Output Push-Pull pin A9, Speed 2 MHz
	GPIOA->CRH &= ~(GPIO_CRH_CNF9_1) & ~(GPIO_CRH_CNF9_0);

	/* FQ_UD (A10) */
	GPIOA->CRH |= GPIO_CRH_MODE10_1 & ~(GPIO_CRH_MODE10_0);  // Output Push-Pull pin A10, Speed 2 MHz
	GPIOA->CRH &= ~(GPIO_CRH_CNF10_1) & ~(GPIO_CRH_CNF10_0);
	/* RESET (A12) */
	GPIOA->CRH |= GPIO_CRH_MODE12_1 & ~(GPIO_CRH_MODE12_0);  // Output Push-Pull pin A12, Speed 2 MHz
	GPIOA->CRH &= ~(GPIO_CRH_CNF12_1) & ~(GPIO_CRH_CNF12_0);
}
void AD9850_ParalelStart(void)
{
	/* RESET Pulse */
	GPIOA->BSRR |= GPIO_BSRR_BS12;
	GPIOA->BSRR |= GPIO_BSRR_BR12;
}
void AD9850_ParalelTransiveByte(uint8_t byte)
{
	GPIOA->ODR &= byte;
	/* W_CLK Pulse */
	GPIOA->BSRR |= GPIO_BSRR_BS9;
	GPIOA->BSRR |= GPIO_BSRR_BR9;
}
void AD9850_ParalelSendFrequancy(double freq)
{
	uint32_t fout = (uint32_t)(freq * 4294967295/125000000);
	for(int i = 0; i < 4; i++, fout >>=8)
	{
		AD9850_ParalelTransiveByte(fout & 0xff);
	}
	AD9850_ParalelTransiveByte(0x00);
	/* FQ_UD Pulse */
	GPIOA->BSRR |= GPIO_BSRR_BS10;
	GPIOA->BSRR |= GPIO_BSRR_BR10;
}
#endif
