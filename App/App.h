#ifndef _APP_H
#define _APP_H

#include "Drv.h"
#include "App_Event.h"

#include "Standby.h"
#include "Mop.h"
#include "IapTester.h"



typedef enum
{
    AppState_Start,             // 刚上电

    AppState_Standby,   // 不工作，电池供电
    AppState_Halt,      // 不工作，电池断电
    AppState_Mop,

    AppState_IapTester,
    AppState_IapMcuUpdata,
} App_State_t;

typedef struct
{
    uint32_t Tick_s;        // 1s累加，Top后维持
    App_State_t State;
    App_State_t State_Last;
} App_t;
extern App_t App;


void App_Init(void);
void App_Task(void);

void AppState_Goto(App_State_t NewState);
void AppState_Goto_Normal(void);

void AppState_Charge_Goto_SelfClean(void);


#endif
