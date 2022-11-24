#include "sADC.h"


sADC_t sADC = {0};


void ADC_Config_RegularChannel(uint8_t channel,uint8_t number,uint8_t sample_time)
{
    
		ADC_Channel_Sample_Time_Config( channel, sample_time );
	
	  ADC_Regular_Sequence_Conversion_Number_Config( channel, number );
}

void ADC_Init(void)
{
		ADC_InitType ADC_InitStructure;
	
    // GPIO
    gpio_init( ADC_DrainValve_GPIO_PORT,    GPIO_MODE_ANALOG, GPIO_SLEW_RATE_FAST, ADC_DrainValve_GPIO_PIN );
    gpio_init( ADC_BrushFanCurrent_GPIO_PORT,    GPIO_MODE_ANALOG, GPIO_SLEW_RATE_FAST, ADC_BrushFanCurrent_GPIO_PIN );
    gpio_init( ADC_RubbishFanCurrent_GPIO_PORT,    GPIO_MODE_ANALOG, GPIO_SLEW_RATE_FAST, ADC_RubbishFanCurrent_GPIO_PIN );
    gpio_init( ADC_PeristalticPumpCurrent_GPIO_PORT,  GPIO_MODE_ANALOG, GPIO_SLEW_RATE_FAST, ADC_PeristalticPumpCurrent_GPIO_PIN );
    gpio_init( ADC_Inflow_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_SLEW_RATE_FAST, ADC_Inflow_GPIO_PIN );
    gpio_init( ADC_NtcTemperature_GPIO_PORT,  GPIO_MODE_ANALOG, GPIO_SLEW_RATE_FAST, ADC_NtcTemperature_GPIO_PIN );
	  gpio_init( ADC_RUBBISH_RX_GPIO_PORT, GPIO_MODE_INPUT, GPIO_SLEW_RATE_FAST, ADC_RUBBISH_RX_GPIO_PIN );
    gpio_init( ADC_RUBBISH_NTC_GPIO_PORT,  GPIO_MODE_ANALOG, GPIO_SLEW_RATE_FAST, ADC_RUBBISH_NTC_GPIO_PIN );
	  gpio_init( ADC_TANK_CLEAR_GPIO_PORT, GPIO_MODE_INPUT, GPIO_SLEW_RATE_FAST, ADC_TANK_CLEAR_GPIO_PIN );
    gpio_init( ADC_RUBBISH_RX2_GPIO_PORT,  GPIO_MODE_ANALOG, GPIO_SLEW_RATE_FAST, ADC_RUBBISH_RX2_GPIO_PIN );
	
    RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_ADC);

    /* RCC_ADCHCLK_DIV16*/
	
	  ADC_Clock_Mode_Config(ADC_CKMOD_AHB,RCC_ADCHCLK_DIV6);
	
    RCC_ADC_1M_Clock_Config(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV16);  //selsect HSE as RCC ADC1M CLK Source	

    ADC_Initializes_Structure(&ADC_InitStructure);
    ADC_InitStructure.MultiChEn      = ENABLE;
    ADC_InitStructure.ContinueConvEn = ENABLE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_REGULAR_T4_CC4;
    ADC_InitStructure.ChsNumber      = ADC_REGULAR_LEN_10;
    ADC_Initializes(&ADC_InitStructure);
    
    /* ADC channel sampletime configuration */
      ADC_Channel_Sample_Time_Config(ADC_Channel_15_PB13, ADC_SAMP_TIME_55CYCLES5);
    /* ADC regular channel configuration */
      ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_15_PB13, ADC_REGULAR_NUMBER_1);
			
			
			    /* ADC channel sampletime configuration */
      ADC_Channel_Sample_Time_Config(ADC_Channel_04_PA3, ADC_SAMP_TIME_55CYCLES5);
    /* ADC regular channel configuration */
      ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_04_PA3, ADC_REGULAR_NUMBER_2);
			
			//ADC_Channel_Sample_Time_Config(ADC_DrainValve_CHANNEL, ADC_SAMP_TIME_55CYCLES5);
			
			/* ADC channel sampletime configuration */
      ADC_Channel_Sample_Time_Config(ADC_Channel_06_PA5, ADC_SAMP_TIME_55CYCLES5);
      /* ADC regular channel configuration */
      ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_06_PA5, ADC_REGULAR_NUMBER_3);
			
			    /* ADC channel sampletime configuration */
      ADC_Channel_Sample_Time_Config(ADC_Channel_08_PA7, ADC_SAMP_TIME_55CYCLES5);
    /* ADC regular channel configuration */
      ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_08_PA7, ADC_REGULAR_NUMBER_4);
			
			    /* ADC channel sampletime configuration */
      ADC_Channel_Sample_Time_Config(ADC_Channel_01_PA0, ADC_SAMP_TIME_55CYCLES5);
    /* ADC regular channel configuration */
      ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_01_PA0, ADC_REGULAR_NUMBER_5);
			
			    /* ADC channel sampletime configuration */
      ADC_Channel_Sample_Time_Config(ADC_Channel_02_PA1, ADC_SAMP_TIME_55CYCLES5);
    /* ADC regular channel configuration */
      ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_02_PA1, ADC_REGULAR_NUMBER_6);
			
      ADC_Channel_Sample_Time_Config(ADC_Channel_12_PB10, ADC_SAMP_TIME_55CYCLES5);
    /* ADC regular channel configuration */
      ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_12_PB10, ADC_REGULAR_NUMBER_7);
    
      ADC_Channel_Sample_Time_Config(ADC_Channel_10_PB1, ADC_SAMP_TIME_55CYCLES5);
    /* ADC regular channel configuration */
      ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_10_PB1, ADC_REGULAR_NUMBER_8);

      ADC_Channel_Sample_Time_Config(ADC_Channel_03_PA2, ADC_SAMP_TIME_55CYCLES5);
    /* ADC regular channel configuration */
      ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_03_PA2, ADC_REGULAR_NUMBER_9);

      ADC_Channel_Sample_Time_Config(ADC_Channel_13_PB11, ADC_SAMP_TIME_55CYCLES5);
    /* ADC regular channel configuration */
      ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_13_PB11, ADC_REGULAR_NUMBER_10);

    /* Enable ADC DMA */
    ADC_DMA_Transfer_Enable();

    /* Enable ADC external trigger */
    ADC_External_Trigger_Conversion_Config(ADC_EXTTRIGCONV_REGULAR_ENABLE);

    /* Enable ADC */
    ADC_ON();
    
    /* Check ADC Ready */
    while(ADC_Flag_Status_Get(ADC_RD_FLAG, ADC_FLAG_JENDCA, ADC_FLAG_RDY) == RESET)
        ;
    
    /* Start ADC1 calibration */
    ADC_Calibration_Operation(ADC_CALIBRATION_ENABLE);
    /* Check the end of ADC1 calibration */
    while (ADC_Calibration_Operation(ADC_CALIBRATION_STS))
        ;
    /* Start ADC Software Conversion */
    ADC_Regular_Channels_Software_Conversion_Operation(ADC_EXTRTRIG_SWSTRRCH_ENABLE);
	
		LOG_DEB("Bsp ADC init finish.");
}
