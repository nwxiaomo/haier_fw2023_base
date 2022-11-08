#include "Bsp.h"

void Bsp_Init(void)
{
	  LOG_DEB("Bsp init start.");
    Mcu_Init();

    Bsp_DMA_Init();

    ADC_Init();
    
    TIM1_Init();
    TIM2_Init();
    TIM3_Init();
    TIM4_Init();
	  TIM5_Init();
		TIM6_Init();
	
		Exti_Init();

    USART1_Init();

    IO_Init(); //IO 初始化放前面会导致定时器1通道1没有输出


    #ifdef WDG_EN
        WDG_Init();
    #endif
		
		LOG_DEB("Bsp init finish.");
}


void Bsp_Start(void)
{
    TIM4_Start();

    #ifdef WDG_EN
        WDG_Start();
    #endif
}




void Bsp_Task(void)
{
    #ifdef WDG_EN
        WDG_Feed();
    #endif
}

