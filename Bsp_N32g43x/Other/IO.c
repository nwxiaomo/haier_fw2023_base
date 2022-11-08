#include "IO.h"


void gpio_init( GPIO_Module* GPIO_Port, uint32_t Mode, uint32_t Gpio_Rate, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_Structure_Initialize(&GPIO_InitStructure);
	
	
	
    GPIO_InitStructure.Pin       = Pin;
    GPIO_InitStructure.GPIO_Mode = Mode;
    GPIO_InitStructure.GPIO_Current   = GPIO_DS_4MA;
	  GPIO_InitStructure.GPIO_Slew_Rate = Gpio_Rate;
	
    GPIO_Peripheral_Initialize(GPIO_Port, &GPIO_InitStructure);

}

void IO_Init(void)
{
    //////// Output ////////
		BRUSH_HEATER_OFF();
	  gpio_init(BRUSH_HEATER_GPIO_PORT,GPIO_MODE_OUT_PP,GPIO_SLEW_RATE_FAST,BRUSH_HEATER_GPIO_PIN);
	
		BRUSH_FAN_CTRL_OFF();
	  gpio_init(BRUSH_FAN_CTRL_GPIO_PORT,GPIO_MODE_OUT_PP,GPIO_SLEW_RATE_FAST,BRUSH_FAN_CTRL_GPIO_PIN);
	
		LOG_DEB("Bsp GPIO init finish.");
	  

	
}

