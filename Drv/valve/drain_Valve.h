#ifndef _DRAIN_VALVE_H
#define _DRAIN_VALVE_H

#include "Drv_Common.h"

#define DRAIN_VALVE_PERIOD   (100)


extern Device_t drain_valve;


void Drain_Valve_Init(void);

void Drain_Valve_Start(void);
void Drain_Valve_Stop(void);

void Drain_Valve_Task(void);



#endif
