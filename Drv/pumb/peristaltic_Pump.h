#ifndef _PERISTALTIC_PUMP_H
#define _PERISTALTIC_PUMP_H

#include "Drv_Common.h"



#define PERISTALTIC_PUMP_PERIOD   (100)

extern Device_t peristaltic_pump;



void Peristaltic_Pump_Init(void);

void Peristaltic_Pump_Start(void);
void Peristaltic_Pump_Stop(void);

void Peristaltic_Pump_Task(void);



#endif
