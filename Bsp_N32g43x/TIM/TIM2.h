#ifndef _TIM2_H
#define _TIM2_H

#include "includes.h"
#include "Bsp.h"

#define TIM_CNT_TOP     (0xFFFF)

void TIM2_Init(void);
uint32_t Bsp_Tim_Cnt_Get(void);


#endif
