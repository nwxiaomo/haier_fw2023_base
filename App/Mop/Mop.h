#ifndef _MOP_H
#define _MOP_H

#include "includes.h"
#include "Drv.h"




typedef enum
{
    MopState_Stop,
    MopState_Start,
    MopState_Run,
    MopState_Error,
    MopState_Shut,
    //
} Mop_State_t;


typedef enum
{
    MopError_None,
    MopError_Base_WaterFull,
} Mop_Error_t;

typedef struct
{
    uint32_t Tick;
    uint32_t Tick_ms;
    //
    uint32_t Mode_Tick;
    //
    Mop_State_t State;
    Mop_Error_t Error;


} Mop_t;
extern Mop_t Mop;



void Mop_Start(void);
void Mop_Shut(void);
void Mop_Stop(void);

void Mop_Task(void);



#endif
