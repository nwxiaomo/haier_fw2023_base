#include "rubbish_Fan.h"



Device_t rubbish_fan = {0};


void Rubbish_Fan_Init(void)
{
	
}

//////// Bsp
void Rubbish_Fan_ON(void)
{
	  RUBBISH_FAN_CTRL_ON();
}

void Rubbish_Fan_Off(void)
{
	  RUBBISH_FAN_CTRL_OFF();
}

//////// 状态跳转
void Rubbish_Fan_Start(void)
{
	Rubbish_Fan_ON();
	rubbish_fan.State = State_Run;
}

void Rubbish_Fan_Stop(void)
{
    Rubbish_Fan_Off();
    rubbish_fan.State = State_Stop;
}

void Rubbish_Fan_Task(void)
{
    if (50 == Mcu.Tick_Loop_100ms)
    {
        switch (rubbish_fan.State)
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
