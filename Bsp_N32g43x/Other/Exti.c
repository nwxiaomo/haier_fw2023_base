#include "Exti.h"

Signal_state zero_check_signal = {0};
Signal_state rubbish_full_signal = {Signal_Trigger_Occur};

Signal_state get_zero_signal(void)
{
	return zero_check_signal;
}
void set_zero_signal(Signal_state newstate)
{
	zero_check_signal = newstate;
}

Signal_state get_rubbish_full_signal(void)
{
	return rubbish_full_signal;
}

void set_rubbish_full_signal(Signal_state newstate)
{
	rubbish_full_signal = newstate;
}

void Exti_Init(void)
{
    //////// GPIO
    gpio_init(ZERO_CHECK_GPIO_PORT, GPIO_MODE_INPUT, GPIO_SLEW_RATE_FAST, ZERO_CHECK_GPIO_PIN);
   // gpio_init(RUBBISH_IR_RX_GPIO_PORT, GPIO_MODE_INPUT, GPIO_SLEW_RATE_FAST, RUBBISH_IR_RX_GPIO_PIN);
	
		RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_AFIO);	

    //////// EXTI
	  
	  GPIO_EXTI_Line_Set(EXTI_LINE_SOURCE12, AFIO_EXTI_PB12);
		//GPIO_EXTI_Line_Set(EXTI_LINE_SOURCE10, AFIO_EXTI_PB10);
	    /*Configure EXTI line*/
	
	  EXTI_InitType EXTI_InitStructure;
	
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE12;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Peripheral_Initializes(&EXTI_InitStructure);
	 
//	  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
//	  EXTI_InitStructure.EXTI_Line    = EXTI_LINE10;
//	  EXTI_Peripheral_Initializes(&EXTI_InitStructure);
	
//		EXTI_Interrupt_Status_Clear(EXTI_LINE10);// 清除标志位
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
		 
//		 if (EXTI_Flag_Status_Get(EXTI_LINE10) != RESET)  // 识别标志位
//     {
//         EXTI_Flag_Status_Clear(EXTI_LINE10);  // 清除标志位
//         EXTI_Interrupt_Status_Clear(EXTI_LINE10);  // 清除标志位

//         /*处理应用程序*/
//			   rubbish_full_signal  = Signal_Trigger_Occur;
//			 
//     }
 }


