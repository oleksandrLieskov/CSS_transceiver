#ifndef UART_H
#define UART_H

void UART_Init(void);
void UART_TranciveByte(uint8_t byte);
void UART_TranciveString(uint8_t *str);
void USART1_IRQHandler(void);
void UART_ReceiveString(uint8_t *buferComand);
uint32_t processingComand(uint8_t *buferComand);

#endif
