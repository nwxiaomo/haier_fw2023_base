#ifndef _BINARY_SWITCH_H
#define _BINARY_SWITCH_H

#include "includes.h"


typedef enum
{
    BinarySwitchState_Unknow,
    BinarySwitchState_Off,
    BinarySwitchState_On,
} BinarySwitch_State_t;

typedef struct 
{
    uint32_t Unknow :1;
    uint32_t Off    :1;
    uint32_t On     :1;
} BinarySwitch_Flag_t;


typedef struct 
{
    BinarySwitch_State_t *pState;   // 新状态
    BinarySwitch_Flag_t *pFlag;
    BinarySwitch_State_t (*pGetNewState)(void);
    uint32_t Elapse;
    uint32_t Off_Tick;
    uint32_t On_Tick;
    uint32_t LastState;             // 上一次的状态
} BinarySwitch_t;


void BinarySwitch_Init(BinarySwitch_t *pBinarySwitch, 
                        BinarySwitch_State_t *pState,
                        BinarySwitch_Flag_t *pFlag,
                        BinarySwitch_State_t (*pGetNewState)(void), uint32_t Elapse);

void BinarySwitch_Task(BinarySwitch_t *pBinarySwitch);



#endif
