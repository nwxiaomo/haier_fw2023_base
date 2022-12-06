#ifndef _DRV_COMMON_H
#define _DRV_COMMON_H

#include "includes.h"
#include "Bsp.h"


typedef enum
{
    State_Stop,
    State_Run,
} Running_State_t;

typedef struct
{
    uint32_t Tick;
	
    Running_State_t State;
	
    /*Test*/
    //uint32_t Test_Cnt;
} Device_t;


#endif
