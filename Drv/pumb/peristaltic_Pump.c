#include "peristaltic_Pump.h"



Device_t peristaltic_pump = {0};


void Peristaltic_Pump_Init(void)
{
	
}

//////// Bsp
void Peristaltic_Pump_ON(void)
{
	  BRUSH_FAN_CTRL_ON();
}

void Peristaltic_Pump_OFF(void)
{
	  BRUSH_FAN_CTRL_OFF();
}

//////// 状态跳转
void Peristaltic_Pump_Start(void)
{
	Peristaltic_Pump_ON();
	peristaltic_pump.State = State_Run;
}

void Peristaltic_Pump_Stop(void)
{
    Peristaltic_Pump_OFF();
    peristaltic_pump.State = State_Stop;
}

void Peristaltic_Pump_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (peristaltic_pump.State)
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
