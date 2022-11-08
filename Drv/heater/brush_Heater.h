#ifndef _BRUSH_HEATER_H
#define _BRUSH_HEATER_H

#include "Drv_Common.h"


#define BRUSH_HEATER_PERIOD   (100)


extern Device_t brush_heater;



void Brush_Heater_Init(void);

void Brush_Heater_Start(void);
void Brush_Heater_Stop(void);

void Brush_Heater_Task(void);

#endif
