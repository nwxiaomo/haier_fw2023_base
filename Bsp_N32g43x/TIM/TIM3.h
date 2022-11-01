#ifndef _TIM3_H
#define _TIM3_H

#include "includes.h"
#include "Bsp.h"


void TIM3_Init(void);
void Bsp_Peristaltic_Pump_Duty_Set(uint32_t duty);


#endif
