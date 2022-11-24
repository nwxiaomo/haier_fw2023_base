#ifndef _TANKCLEAR_H
#define _TANKCLEAR_H

#include "Drv_Common.h"

#define TANK_CLEAR_PERIOD   (100)

extern Device_t tankclear_pump;


void Tank_Clear_Init(void);

void Tank_Clear_Inject_Start(void);
void Tank_Clear_Inject_Stop(void);

void Tank_Clear_Inject_Task(void);


#endif
