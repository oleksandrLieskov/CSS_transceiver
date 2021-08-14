#define _SERIAL_COMUNICATION_H
//#define _PARALEL_COMUNICATION_H

#define FREQ_BASE_GENERATOR 125000000u
#define INT_MAX             4294967295u

#ifdef _SERIAL_COMUNICATION_H

void Delay(void);
void AD9850_GPIO_Init(void);
void AD9850_SerialStart(void);
void AD9850_SerialTransiveByte(uint8_t byte);
void AD9850_SerialSendFrequancy(double freq);
void AD9850_CSS_SendString(uint8_t* comandBufer);
void AD9850_CSS_SendChar(uint8_t byte);
void AD9850_CSS_Low(void);
void AD9850_CSS_High(void);

#endif

#ifdef _PARALEL_COMUNICATION_H

void AD9850_GPIO_Init(void);
void AD9850_ParalelStart(void);
void AD9850_ParalelTransiveByte(uint8_t byte);
void AD9850_ParalelSendFrequancy(double freq);

#endif
