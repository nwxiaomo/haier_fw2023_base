#ifndef _TIM8_H
#define _TIM8_H

#include "includes.h"
#include "Bsp.h"


void TIM8_Init(void);

void Bsp_Tank_Clear_Pump_Duty_Set(uint32_t Duty);

#endif
