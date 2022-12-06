#ifndef _IO_H
#define _IO_H

#include "includes.h"


// BRUSH HEAT
#define BRUSH_HEATER_GPIO_PORT		GPIOA
#define BRUSH_HEATER_GPIO_PIN		  GPIO_PIN_15
#define BRUSH_HEATER_ON()			    {GPIO_Pins_Set(BRUSH_HEATER_GPIO_PORT,BRUSH_HEATER_GPIO_PIN);}// ??? 
#define BRUSH_HEATER_OFF()			  {GPIO_Pins_Reset (BRUSH_HEATER_GPIO_PORT,BRUSH_HEATER_GPIO_PIN);}// ???

//BRUSH FAN CTRL
#define BRUSH_FAN_CTRL_GPIO_PORT         GPIOA
#define BRUSH_FAN_CTRL_GPIO_PIN          GPIO_PIN_3
#define BRUSH_FAN_CTRL_OFF()             {GPIO_Pins_Reset(BRUSH_FAN_CTRL_GPIO_PORT,BRUSH_FAN_CTRL_GPIO_PIN);} 
#define BRUSH_FAN_CTRL_ON()              {GPIO_Pins_Set(BRUSH_FAN_CTRL_GPIO_PORT,BRUSH_FAN_CTRL_GPIO_PIN);} 



void gpio_init( GPIO_Module *GPIO_Port, uint32_t Mode, uint32_t Gpio_Rate, uint16_t Pin);

void IO_Init(void);



#endif
