#ifndef _BRUSH_HEATER_H
#define _BRUSH_HEATER_H

#include "Drv_Common.h"


#define BRUSH_HEATER_PERIOD   (100)

typedef enum
{
	HEATER_NORMAL,
	HEATER_ABNORMAL,
}Heater_State;

typedef struct
{
	Device_t device;
	Heater_State working_state;
	
}brush_heater_info_t; 


extern brush_heater_info_t brush_heater;



void Brush_Heater_DeInit(void);

void Brush_Heater_Start(void);
void Brush_Heater_Stop(void);

void Brush_Heater_Task(void);

#endif
