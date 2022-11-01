#ifndef _STANDBY_H
#define _STANDBY_H

#include "includes.h"


typedef struct 
{
    uint32_t Tick;
} Standby_t;
extern Standby_t Standby;


void Standby_Start(void);
void Standby_Stop(void);
void Standby_Task(void);



#endif
