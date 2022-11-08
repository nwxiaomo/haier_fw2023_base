#include "Mop.h"
#include "App_Event.h"
#include "Mop_Smart.h"


Mop_t Mop = {0};


// 只留风扇电机
void Mop_Step_Shut(void)
{
		Drv_Stop_All();
    Fan_Start();
	  Brush_Fan_Start();
		Rubbish_Fan_Start();
}

// 全部关闭
void Mop_Step_Off(void)
{
		Drv_Stop_All();
}



void Mop_Start(void)
{
    
    Mop.Tick = 0; 
    Mop.State = MopState_Start;
    //
    Mop.Tick_ms = 0;
    Mop.Mode_Tick = 0;

    //
}

void Mop_Shut(void)
{
	Mop.Tick = 0;
	    
	if (brush_fan.State == State_Run)    // 正常shut流程
    {
        Mop_Step_Shut();

        Mop.Error = MopError_None;
        Mop.State = MopState_Shut;
    }
    else
    {
        rt_mb_send(mb_AppEvent, AppEvent_Goto_Standby);
    }
}

void Mop_Stop(void)
{  
    Mop.Tick = 0;
    Mop_Step_Off();
    
    Mop.Error = MopError_None;
    Mop.State = MopState_Stop;
}

void Mop_Error(Mop_Error_t Error)
{
    Mop.Tick = 0;
    Mop_Step_Off();
    Mop.Error = Error;
    Mop.State = MopState_Error;
}

// 1ms
void Mop_Task(void)
{
    switch (Mop.State)
    {
        case MopState_Stop:
            break;

        case MopState_Start:
			// 底座水满
				  LOG_DEB("The mop state is start.");
					if (base_module.Base_Inflow_Info.ModuleState == 1)
					{
						LOG_ERR("mop error:[water full]");
						Mop_Error(MopError_Base_WaterFull);
					}
					else
					{
						Mop.Tick = 0;
						Mop.State = MopState_Run;
					}
            break;
        
        case MopState_Run:
            //////// 故障检测
					// 底座水满
					LOG_DEB("The mop state is run.");
					if (base_module.Base_Inflow_Info.ModuleState == 1)
					{	
						LOG_ERR("mop error:[water full]");
						Mop_Error(MopError_Base_WaterFull);
					}
		
            break;
        
        case MopState_Error:
			// 底座水位正常
            if (base_module.Base_Inflow_Info.ModuleState == 0)
            {
							rt_mb_send(mb_AppEvent, AppEvent_Goto_Standby);
            }
            break;

        case MopState_Shut:
						Mop.Tick++;
						LOG_DEB("The mop state is shut.");
						if (Mop.Tick >= ELAPSE_s(1))   // 等待PTC散热完成  ELAPSE_min(2)
									{
											Mop.Tick = 0;
											Fan_Stop();
											Brush_Fan_Stop();
											Rubbish_Fan_Stop();
											rt_mb_send(mb_AppEvent, AppEvent_Goto_Standby);
									}
            break;

        default:
            break;
    }
}
