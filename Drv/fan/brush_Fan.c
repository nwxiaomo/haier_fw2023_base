#include "brush_Fan.h"



Device_t brush_fan = {0};


void Brush_Fan_Init(void)
{
	
}

//////// Bsp
void Brush_Fan_ON(void)
{
	  BRUSH_FAN_CTRL_ON();
}

void Brush_Fan_OFF(void)
{
	  BRUSH_FAN_CTRL_OFF();
}

//////// 状态跳转
void Brush_Fan_Start(void)
{
	Brush_Fan_ON();
	brush_fan.State = State_Run;
}

void Brush_Fan_Stop(void)
{
    Brush_Fan_OFF();
    brush_fan.State = State_Stop;
}

void Brush_Fan_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (brush_fan.State)
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
