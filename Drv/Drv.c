#include "Drv.h"


void Drv_Init(void)
{
    Iap_Init();   
}


void Drv_Task(void)
{
    
    Iap_Task();		// 10ms
	
	  Monitor_Task();
		Brush_Heater_Task();
}

void Drv_Start_All(void)
{
	  BRUSH_FAN_CTRL_ON();
    Brush_Heater_Start();
}

void Drv_Stop_All(void)
{

		Brush_Heater_Stop();
		
		Brush_Fan_Stop();

}





