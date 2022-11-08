#include "TIM3.h"

// TIM3_CH3 PB0    Peristaltic_Pump

void TIM3_Init(void)
{
   TIM_TimeBaseInitType TIM_TimeBaseStructure;
   OCInitType TIM_OCInitStructure;
	
	 RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_TIM3);

    /* Time base configuration */
    TIM_TimeBaseStructure.Period    =  1000 -1;
    TIM_TimeBaseStructure.Prescaler = (uint16_t)( Cal_General_TIM_CLock() / 1000 / 1000) - 1;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
	
    TIM_Base_Initialize(TIM3, &TIM_TimeBaseStructure);
	
		TIM_Interrupt_Enable(TIM3,TIM_INT_UPDATE);

		NVIC_InitType NVIC_InitStructure;
		
		NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PRE_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = NVIC_SUB_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Initializes(&NVIC_InitStructure);
    /* TIM enable counter */
    TIM_On(TIM3);
		
}

extern rt_sem_t sem_UserTick_1ms;
// 1ms
void TIM3_IRQHandler()
{
	rt_interrupt_enter();
	
	if(TIM_Interrupt_Status_Get(TIM3,TIM_INT_UPDATE) != RESET)
	{
		rt_sem_release(sem_UserTick_1ms);
		TIM_Interrupt_Status_Clear(TIM3,TIM_INT_UPDATE);
	}
	rt_interrupt_leave();
}
