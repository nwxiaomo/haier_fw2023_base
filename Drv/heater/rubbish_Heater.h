#ifndef _RUBBISH_HEATER_H
#define _RUBBISH_HEATER_H

#include "Drv_Common.h"

#define RUBBISH_HEATER_PERIOD   (100)

extern Device_t rubbish_heater;


void Rubbish_Heater_Init(void);

void Rubbish_Heater_Start(void);
void Rubbish_Heater_Stop(void);

void Rubbish_Heater_Task(void);



#endif
