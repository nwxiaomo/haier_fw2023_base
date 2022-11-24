#ifndef _MONITOR_H
#define _MONITOR_H

#include "Drv_Common.h"
#include "Drv.h"

#define DRAIN_VALUE_WORKING_THRESHOLD        (2800)   // 0.5V
#define PERISTALTIC_PUMP_WORKING_THRESHOLD   (100)
#define RUBBISH_FAN_WORK_THRESHOLD           (100)
#define BRUSH_FAN_WORK_THRESHOLD             (100)
#define BASE_INFLOW_THRESHOLD                (2800)
#define BASE_NTC_THRESHOLD                   (3800)
#define RUBBISH_DRYING_NTC_THRESHOLD         (2800)
#define TANK_CLEAR_PUMP_THRESHOLD            (2800)
#define TRASH_BASKET_RX_THRESHOLD            (2800)
#define TRASH_BASKET_RX2_THRESHOLD           (2800)


#define TRASH_BASKET_FULL_CHECK_DELAY        (60) //3s
#define ZERO_SIGNAL_CHECK_DELAY              (20) //3s

typedef enum 
{
    Working_State_Reset = 0,   //�رչ���״̬
    Working_State_Set,     //����״̬
} Working_State;

typedef struct{
	Working_State ModuleState;
	uint32_t Voltage;
	uint32_t Check_Delay;
}Module_Info_t;


typedef struct {
	
	Module_Info_t Drain_Valve_Info;
	Module_Info_t Peristaltic_Pump_Info;
	Module_Info_t Rubbish_Fan_Info;
	Module_Info_t Brush_Fan_Info;
	Module_Info_t Base_Inflow_Info;
	Module_Info_t Base_NTC_Info;
	Module_Info_t Trash_Basket_Info; //垃圾在位检测
	Module_Info_t Trash_Basket_Full_Info;
	Module_Info_t Cleaning_Material_Info;
	Module_Info_t Drain_Valve_liquid_Info;
	Module_Info_t Alternating_Current_Zero_Info;

	Module_Info_t Rubbish_Drying_NTC_Info;
	Module_Info_t Tank_Clear_Pump_Info;
	
	Module_Info_t Tank_Clear_Full_Info;
	Module_Info_t Tank_Clear_Not_Water_Info;

	Module_Info_t Drain_Valve_On_Left_Info;
	Module_Info_t Drain_Valve_On_Right_Info;
	


}Module_t;

extern Module_t base_module;




#define MONITOR_PERIOD              (10)

void Monitor_Init(void);
void Monitor_Task(void);


#endif
