#ifndef _RUBBISH_FAN_H
#define _RUBBISH_FAN_H

#include "Drv_Common.h"


#define RUBBISH_FAN_PERIOD   (100)


extern Device_t rubbish_fan;



void Rubbish_Fan_Init(void);

void Rubbish_Fan_Start(void);
void Rubbish_Fan_Stop(void);

void Rubbish_Fan_Task(void);



#endif
