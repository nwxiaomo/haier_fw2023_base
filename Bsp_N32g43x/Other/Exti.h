#ifndef _EXTI_H
#define _EXTI_H

#include "includes.h"
#include "Bsp.h"


typedef enum{
	Signal_Trigger_Unknow,
	Signal_Trigger_Occur,
	Signal_Trigger_Waitting,
}Signal_state;

extern Signal_state zero_check_signal;
extern Signal_state rubbish_full_signal;


#define ZERO_CHECK_GPIO_PORT    GPIOB
#define ZERO_CHECK_GPIO_PIN     GPIO_PIN_12
#define ZERO_CHECK_READ()       (GPIO_ReadInputDataBit(ZERO_CHECK_GPIO_PORT,ZERO_CHECK_GPIO_PIN))


void Exti_Init(void);
Signal_state get_zero_signal(void);
void set_zero_signal(Signal_state newstate);

Signal_state get_rubbish_full_signal(void);
void set_rubbish_full_signal(Signal_state newstate);

#endif
