#ifndef _TIM1_H
#define _TIM1_H

#include "includes.h"
#include "Bsp.h"


void TIM1_Init(void);

//void Bsp_Drain_Valve_Duty_Set(uint32_t Duty);
void Bsp_Cooling_Fan_Duty_Set(uint32_t Duty);
void Bsp_Rubbish_Heater_Duty_Set(uint32_t Duty);
void Bsp_Brush_Heater_Duty_Set(uint32_t Duty);

#endif
