#ifndef _BRUSH_FAN_H
#define _BRUSH_FAN_H

#include "Drv_Common.h"



#define BRUSH_FAN_PERIOD   (100)

extern Device_t brush_fan;



void Brush_Fan_Init(void);

void Brush_Fan_Start(void);
void Brush_Fan_Stop(void);

void Brush_Fan_Task(void);



#endif
