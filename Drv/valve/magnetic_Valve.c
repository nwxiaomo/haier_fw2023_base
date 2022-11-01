#include "magnetic_Valve.h"


Device_t magnetic_valve = {0};


void Magnetic_Valve_Init(void)
{
	
}

//////// Bsp
void Magnetic_Valve_ON(void)
{
	  MAGNETIC_VALVE_CTRL_ON();
}

void Magnetic_Valve_Off(void)
{
	  MAGNETIC_VALVE_CTRL_OFF();
}

//////// 状态跳转
void Magnetic_Valve_Start(void)
{
	Magnetic_Valve_ON();
	magnetic_valve.State = State_Run;
}

void Magnetic_Valve_Stop(void)
{
    Magnetic_Valve_Off();
    magnetic_valve.State = State_Stop;
}

void Magnetic_Valve_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (magnetic_valve.State)
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
