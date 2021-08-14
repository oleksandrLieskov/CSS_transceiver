/*
 * Timer.h
 *
 *  Created on: 24 трав. 2021 р.
 *      Author: Admin
 */

#ifndef INC_DWT_H_
#define INC_DWT_H_

#define DWT_CONTROL *(volatile unsigned long *)0xE0001000
#define SCB_DEMCR   *(volatile unsigned long *)0xE000EDFC

void DWT_Init(void);
void delay_mk(uint32_t us);

#endif /* INC_DWT_H_ */
