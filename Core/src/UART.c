#include "main.h"

extern uint8_t flag;
extern uint8_t rxSymbol;

void UART_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Clock port A ON
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	/*UART1 Tx-PA9, Rx-PA10*/
	GPIOA->CRH |=  GPIO_CRH_CNF9_1;
	GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
	GPIOA->CRH |=  GPIO_CRH_MODE9_1;
	GPIOA->CRH &= ~GPIO_CRH_MODE9_0;

	GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
	GPIOA->CRH |=  GPIO_CRH_CNF10_0;
	GPIOA->CRH &= ~GPIO_CRH_MODE10_1;
	GPIOA->CRH &= ~GPIO_CRH_MODE10_0;

	USART1->BRR = 0x271;

	USART1->CR1 |= USART_CR1_UE;
	USART1->CR1 |= USART_CR1_RE;
	USART1->CR1 |= USART_CR1_TE;
	USART1->CR1 |= USART_CR1_RXNEIE;

	NVIC_EnableIRQ(USART1_IRQn);
}
void UART_TranciveByte(uint8_t byte)
{
	while(!(USART1->SR & USART_SR_TXE));
	USART1->DR = byte;
}

void UART_TranciveString(uint8_t *str)
{
	int i = 0u;
	while(str[i] != '\0')
	{
		UART_TranciveByte(str[i]);
		i++;
	}
}

void USART1_IRQHandler(void)
{
	if(USART1->SR & USART_SR_RXNE)
	{
		rxSymbol = USART1->DR;
		flag = 1u;
	}
}

void UART_ReceiveString(uint8_t *buferComand)
{
	uint8_t count = 0u;
	while(!flag){}
	flag = 0u;
	buferComand[count] = rxSymbol;
	while(buferComand[count] != 'A')
	{
		count++;
		while(!flag){}
		flag = 0;
		buferComand[count] = rxSymbol;
	}
}

uint32_t processingComand(uint8_t *buferComand)
{
	uint8_t *duration;
	uint8_t sep[] = "-";
	uint32_t b;

	if(buferComand[0] == 's')
	{
		if(buferComand[1] == 'f')
		{
			duration = strtok(buferComand, sep);
			while(duration != NULL)
			{
				b = atoi(duration);
				if(b > 0)
				{
					AD9850_SerialSendFrequancy((double)b);
				}
				duration = strtok(NULL, sep);
			}
		}
		if(buferComand[1] == 'p')
		{
			duration = strtok(buferComand, sep);
			while(duration != NULL)
			{
				b = atoi(duration);
				if(b > 0)
				{
					/* Функція передачі фази */
				}
				duration = strtok(NULL, sep);
			}
		}
	}
	memset(buferComand, 0, 19);
}



