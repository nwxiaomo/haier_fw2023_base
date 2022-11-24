#ifndef _DRAIN_VALVE_H
#define _DRAIN_VALVE_H

#include "Drv_Common.h"

#define DRAIN_VALVE_PERIOD   (100)

#define DRAIN_MAX_DUTY       (1000 -1)
#define DRAIN_FORWARD_DUTY   (600)
#define DRAIN_BACKWARD_DUTY  (DRAIN_MAX_DUTY - DRAIN_FORWARD_DUTY) //和正转互补

typedef enum
{
	DRAIN_VALVE_UNKNOW,
	DRAIN_VALVE_FORWARD,
	DRAIN_VALVE_BACKWARD,
	DRAIN_VALVE_STOP
}Running_Direction;

typedef struct
{
	Device_t device;
	Running_Direction last_running_state;

}Drain_Valve_Info_t;

extern Drain_Valve_Info_t drain_valve_info;


void Drain_Valve_Init(void);

void Drain_Valve_Forward(void);
void Drain_Valve_Backward(void);

void Drain_Valve_Start(Running_Direction running_state);
void Drain_Valve_Stop(void);

void Drain_Valve_Task(void);



#endif
