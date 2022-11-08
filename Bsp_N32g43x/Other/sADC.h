#ifndef _S_ADC_H
#define _S_ADC_H

#include "includes.h"
#include "Bsp.h"


//////// ADC值 转换成 电压值mV
//#define ADC_2_VOLTAGE(x)    ((uint32_t)(x) *3300 /4095)
//#define ADC_2_VOLTAGE(x)    ((uint32_t)(x) *1100 /1365)
//#define ADC_2_VOLTAGE(x)    ((uint32_t)(x) *220 /273)     // 4095*220 = 900900 = 0xDBF24
//#define ADC_2_VOLTAGE(x)    ((uint32_t)(x) *219 /273)
#define ADC_2_VOLTAGE(x)    ((uint32_t)(x) *73 /91)       // 4095*73 = 298935 = 0x48FB7


//#define VOLTAGE_2_ADC(x)    ((uint32_t)(x) *4095 /3300)
#define VOLTAGE_2_ADC(x)    ((uint32_t)(x) *273 /220)


//滚筒风扇电流检测
#define ADC_BrushFanCurrent_CHANNEL              ADC_Channel_05_PA4
#define ADC_BrushFanCurrent_GPIO_PORT            GPIOA
#define ADC_BrushFanCurrent_GPIO_PIN             GPIO_PIN_4

//进水检测
#define ADC_Inflow_CHANNEL                        ADC_Channel_03_PA2
#define ADC_Inflow_GPIO_PORT                      GPIOA
#define ADC_Inflow_GPIO_PIN                       GPIO_PIN_2

//NTC温度检测
#define ADC_NtcTemperature_CHANNEL                ADC_Channel_10_PB1
#define ADC_NtcTemperature_GPIO_PORT              GPIOB
#define ADC_NtcTemperature_GPIO_PIN               GPIO_PIN_1


//////// 使用的通道序号，总个数
typedef enum
{
		ADC_CH_BrushFanCurrent,            // 0
		ADC_CH_Inflow,                     // 1
		ADC_CH_NtcTemperature,             // 2
		ADC_CH_SIZE                        // 通道总个数
} ADC_CH_t;

#define ADC_BUF_SIZE    (10 * 2)     // 缓存大小，循环存储
typedef struct
{
    volatile uint16_t Value_Record[ADC_BUF_SIZE][ADC_CH_SIZE];
    //
    uint16_t Value_Filtered_Half[ADC_CH_SIZE];     // DMA半中断，前10的平均数
    uint16_t Value_Filtered_Full[ADC_CH_SIZE];     // DMA全中断，后10组平均数
    //
    uint16_t Value_Filtered_0p5ms[ADC_CH_SIZE];
    uint16_t Value_Filtered_1ms[ADC_CH_SIZE];
} sADC_t;
extern sADC_t sADC;


void ADC_Init(void);




#endif
