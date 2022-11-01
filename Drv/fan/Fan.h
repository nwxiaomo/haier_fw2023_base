#ifndef _FAN_H
#define _FAN_H

#include "Drv_Common.h"


#define FAN_PERIOD   (100)

extern Device_t Fan;


void Fan_Init(void);

void Fan_Start(void);
void Fan_Stop(void);

void Fan_Task(void);



#endif
