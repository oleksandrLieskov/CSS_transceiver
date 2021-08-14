/*
 * Timer.c
 *
 *  Created on: 24 трав. 2021 р.
 *      Author: Admin
 */

// Data Watchpoint and Trace unit

#include "main.h"

void DWT_Init(void)
{
    SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk;
}

void delay_mk(uint32_t us)
{
    uint32_t us_count_tic =  us * (SystemCoreClock / 1000000);
    DWT->CYCCNT = 0U;
    while(DWT->CYCCNT < us_count_tic);
}
