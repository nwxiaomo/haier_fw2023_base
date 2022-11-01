#ifndef _IAP_TESTER_H
#define _IAP_TESTER_H

#include "includes.h"
#include "Drv.h"



typedef struct
{
    uint32_t Tick;
    //
    enum
    {
        TesterScreenState_Off,
        TesterScreenState_Red,
        TesterScreenState_Green,
        TesterScreenState_Blue,
        TesterScreenState_White,
    } Screen_State;

} IapTester_t;
extern IapTester_t IapTester;




void IapTester_Start(void);
void IapTester_Stop(void);
void IapTester_Task(void);



#endif
