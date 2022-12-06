#ifndef _MONITOR_H
#define _MONITOR_H

#include "Drv_Common.h"
#include "Drv.h"

#define BRUSH_FAN_WORK_THRESHOLD_MAX             (1200)
#define BRUSH_FAN_WORK_THRESHOLD_MIN             (10)
#define BASE_INFLOW_THRESHOLD                (2800)
#define BASE_NTC_THRESHOLD                   (620)

typedef enum 
{
    Working_State_Reset = 0,   //关闭工作状态
    Working_State_Set,     //工作状态
} Working_State;

typedef struct{
	Working_State ModuleState;
	uint32_t Voltage;
	uint32_t Check_Delay;
}Module_Info_t;


typedef struct {
	
	Module_Info_t Brush_Fan_Info;
	Module_Info_t Base_Inflow_Info;
	Module_Info_t Base_NTC_Info;

	
}Module_t;

extern Module_t base_module;




#define MONITOR_PERIOD              (10)

void Monitor_Init(void);
void Monitor_Task(void);


#endif
