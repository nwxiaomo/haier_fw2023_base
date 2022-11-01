#ifndef _DRV_H
#define _DRV_H

//#include "includes.h"
#include "Bsp.h"
#include "Fan.h"
#include "Iap.h"
#include "brush_Heater.h"
#include "rubbish_Heater.h"
#include "drain_Valve.h"
#include "magnetic_Valve.h"
#include "led.h"
#include "brush_Fan.h"
#include "rubbish_Fan.h"
#include "Drv_Common.h"
#include "peristaltic_Pump.h"
#include "monitor.h"


void Drv_Init(void);
void Drv_Task(void);

void Drv_Start_All(void);
void Drv_Stop_All(void);


#endif
