#include "Drv.h"




void Drv_Init(void)
{
	
    Fan_Init();
    Iap_Init();
		All_Led_Close();
    
}


void Drv_Task(void)
{
    
    Fan_Task();		// 10ms
    Iap_Task();		// 10ms
	
	  Monitor_Task();
		Brush_Heater_Task();
		Rubbish_Heater_Task();

	
		Led_Task();
}

void Drv_Start_All(void)
{
	  Inhale_Duty_Set(20);
	  Bsp_Rubbish_Heater_Duty_Set(350); //200 50° 260 52°  1khz?pwm?? 350???? ??????
	  Bsp_Brush_Heater_Duty_Set(999);
	
	  Bsp_Peristaltic_Pump_Duty_Set(600);
	
	  Bsp_Drain_Valve_Duty_Set(999);
	
	  BRUSH_FAN_CTRL_ON();
		RUBBISH_FAN_CTRL_ON();
		
		MAGNETIC_VALVE_CTRL_ON();
}

void Drv_Stop_All(void)
{
		Fan_Stop();
		Brush_Heater_Stop();
		
		Rubbish_Heater_Stop();
		
		Drain_Valve_Stop();
		Magnetic_Valve_Stop();
		Brush_Fan_Stop();
		Rubbish_Fan_Stop();
		Peristaltic_Pump_Stop();
}





