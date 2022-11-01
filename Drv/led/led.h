#ifndef _LED_H
#define _LED_H

#include "Drv_Common.h"


#define LED_PERIOD   (100)

extern Device_t rubbish_full_led;
extern Device_t clean_led;
extern Device_t fault_led;

void Led_Init(void);

void Rubbish_Full_Led_Start(void);
void Rubbish_Full_Led_Stop(void);

void Clean_Led_Start(void);
void Clean_Led_Stop(void);

void Fault_Led_Start(void);
void Fault_Led_Stop(void);

void All_Led_Close(void);

void Led_Task(void);



#endif
