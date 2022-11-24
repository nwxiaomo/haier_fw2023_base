#ifndef _LED_H
#define _LED_H

#include "Drv_Common.h"


#define LED_PERIOD   (100)

typedef void ( * led_ctrl_func )(void); 

typedef enum
{
    LedState_Off,
    LedState_On,
    LedState_FlashSlow,
    LedState_FlashFast,
    LedState_Breath,    // 
} Led_State_t;

extern Device_t rubbish_full_led;
extern Device_t clean_led;
extern Device_t fault_led;

typedef struct{
    Led_State_t led_state;
    Device_t led_device;
    led_ctrl_func led_on;
    led_ctrl_func led_off;
}led_info_t;

typedef struct{
    led_info_t rubbish_full_led;
    led_info_t clean_led;
    led_info_t fault_led;
}led_list_t;

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
