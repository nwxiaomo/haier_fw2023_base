#include "drain_Valve.h"



Device_t drain_valve = {0};


void Drain_Valve_Init(void)
{
	
}

//////// Bsp
void Drain_Valve_ON(void)
{
	  Bsp_Drain_Valve_Duty_Set(999);
}

void Drain_Valve_Off(void)
{
	  Bsp_Drain_Valve_Duty_Set(0);
}

//////// 状态跳转
void Drain_Valve_Start(void)
{
	Drain_Valve_ON();
	drain_valve.State = State_Run;
}

void Drain_Valve_Stop(void)
{
    Drain_Valve_Off();
    drain_valve.State = State_Stop;
}

void Drain_Valve_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (drain_valve.State)
        {
            case State_Stop:
                break;

            case State_Run:
                break;

            default:		
				
                break;
        }
    }
}
