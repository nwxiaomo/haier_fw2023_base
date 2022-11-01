#ifndef _MAGNETIC_VALVE_H
#define _MAGNETIC_VALVE_H

#include "Drv_Common.h"

#define MAGNETIC_VALVE_PERIOD   (100)

extern Device_t magnetic_valve;



void Magnetic_Valve_Init(void);

void Magnetic_Valve_Start(void);
void Magnetic_Valve_Stop(void);

void Magnetic_Valve_Task(void);



#endif
