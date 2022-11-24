#include "Exti.h"
#include "drain_Valve.h"

Signal_state zero_check_signal = {0};
Signal_state drain_on_left_signal = {Signal_Trigger_Occur};
Signal_state drain_on_right_signal = {Signal_Trigger_Occur};

Signal_state get_zero_signal(void)
{
	return zero_check_signal;
}
void set_zero_signal(Signal_state newstate)
{
	zero_check_signal = newstate;
}

Signal_state get_drain_on_left_signal(void)
{
	return drain_on_left_signal;
}

void set_drain_on_left_signal(Signal_state newstate)
{
	drain_on_left_signal = newstate;
}

Signal_state get_drain_on_right_signal(void)
{
	return drain_on_right_signal;
}

void set_drain_on_right_signal(Signal_state newstate)
{
	drain_on_right_signal = newstate;
}


void Exti_Init(void)
{
    //////// GPIO
    gpio_init(ZERO_CHECK_GPIO_PORT, GPIO_MODE_INPUT, GPIO_SLEW_RATE_FAST, ZERO_CHECK_GPIO_PIN);
    gpio_init(DRAIN_VALVE_LEFT_SENSE_PORT, GPIO_MODE_INPUT, GPIO_SLEW_RATE_FAST, DRAIN_VALVE_LEFT_SENSE_PIN);
    gpio_init(DRAIN_VALVE_RIGHT_SENSE_PORT, GPIO_MODE_INPUT, GPIO_SLEW_RATE_FAST, DRAIN_VALVE_RIGHT_SENSE_PIN);
	
		RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_AFIO);	

    //////// EXTI
	  
	  GPIO_EXTI_Line_Set(EXTI_LINE_SOURCE12, AFIO_EXTI_PD12);
    GPIO_EXTI_Line_Set(EXTI_LINE_SOURCE11, AFIO_EXTI_PB13);
    GPIO_EXTI_Line_Set(EXTI_LINE_SOURCE10, AFIO_EXTI_PB12);
		//GPIO_EXTI_Line_Set(EXTI_LINE_SOURCE10, AFIO_EXTI_PB10);
	    /*Configure EXTI line*/
	
	  EXTI_InitType EXTI_InitStructure;
	
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE12;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Peripheral_Initializes(&EXTI_InitStructure);

    EXTI_InitStructure.EXTI_Line    = EXTI_LINE11;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Peripheral_Initializes(&EXTI_InitStructure);
	 
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE10;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Peripheral_Initializes(&EXTI_InitStructure);

	  EXTI_Interrupt_Status_Clear(EXTI_LINE10);// 清除标志位
    EXTI_Interrupt_Status_Clear(EXTI_LINE11);// 清除标志位
		EXTI_Interrupt_Status_Clear(EXTI_LINE12);// 清除标志位
		
    /*Set key input interrupt priority*/
		
		NVIC_InitType NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PRE_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = NVIC_SUB_PRIORITY;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Initializes(&NVIC_InitStructure);
		
		LOG_DEB("Bsp EXIT init finish.");
		
}

 void EXTI15_10_IRQHandler(void)
 {
     if (EXTI_Flag_Status_Get(EXTI_LINE12) != RESET)  // 识别标志位
     {
         EXTI_Flag_Status_Clear(EXTI_LINE12);  // 清除标志位
         EXTI_Interrupt_Status_Clear(EXTI_LINE12);  // 清除标志位
         zero_check_signal = Signal_Trigger_Occur;
         /*处理应用程序*/
     }
		 
		if (EXTI_Flag_Status_Get(EXTI_LINE11) != RESET)  // 识别标志位
    {
        EXTI_Flag_Status_Clear(EXTI_LINE11);  // 清除标志位
        EXTI_Interrupt_Status_Clear(EXTI_LINE11);  // 清除标志位

        /*处理应用程序*/
			   drain_on_left_signal  = Signal_Trigger_Occur;
         Drain_Valve_Stop();//到达位置之后立马停止
			 
    }

 		if (EXTI_Flag_Status_Get(EXTI_LINE10) != RESET)  // 识别标志位
    {
        EXTI_Flag_Status_Clear(EXTI_LINE10);  // 清除标志位
        EXTI_Interrupt_Status_Clear(EXTI_LINE10);  // 清除标志位

        /*处理应用程序*/
			   drain_on_right_signal  = Signal_Trigger_Occur;
         Drain_Valve_Stop();//到达位置之后立马停止
    }
 }


