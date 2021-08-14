#include "main.h"

uint8_t comandBufer[20] = {0};
uint8_t flag = 0;
uint8_t rxSymbol;

float i = 1.0;


int main(void)
{
	RCC_Init();
	AD9850_GPIO_Init();
	UART_Init();
	AD9850_SerialStart();
	DWT_Init();
	while(1)
	{
		AD9850_CSS_SendChar(0xAA);

	}
	return 0;
}



