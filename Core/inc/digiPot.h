#ifndef DIGI_POT_H
#define DIGI_POT_H

#define MINIMUM_INCREMENT 100

void digiPot_GPIO_Init(void);
void digiPot_AdjustToZero(void);
void digiPot_SetRes(int16_t resValue);

#endif
