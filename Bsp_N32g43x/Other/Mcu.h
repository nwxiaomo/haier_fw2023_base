#ifndef _MCU_H
#define _MCU_H

#include "includes.h"


//////// 系统时钟
#define MCU_FREQ_Hz    ((uint32_t)(120000000))              // 120MHz
#define MCU_FREQ_MHz   ((uint8_t)(MCU_FREQ_Hz / 1000000u))

//////// 默认的优先级
#define NVIC_PRE_PRIORITY   (1)     // 组优先级
#define NVIC_SUB_PRIORITY   (1)     // 子优先级



//////// Delay
#define USER_TICK_PERIOD	((uint8_t)(1))       // 1表示1ms
//
#define ELAPSE_ms(x)        ((x) / USER_TICK_PERIOD)
#define ELAPSE_s(x)         ((x) * 1000 / USER_TICK_PERIOD)
#define ELAPSE_min(x)       ((x) * 1000 * 60 / USER_TICK_PERIOD)
#define ELAPSE_h(x)         ((x) * 1000 * 60 * 60 / USER_TICK_PERIOD)




typedef struct
{
    uint32_t Tick_ms;           // 1ms累加，Top后维持
    //
    uint32_t Tick_Loop_1ms;     // 1ms累加，Top后循环
    uint32_t Tick_Loop_10ms;    // 1ms累加，10ms循环，0~9
    uint32_t Tick_Loop_100ms;   // 1ms累加，100ms循环，0~99
    uint32_t Tick_Loop_1000ms;  // 1ms累加，1000ms循环，0~999

    uint32_t Tick_Loop_3s;
    //

    uint32_t Tick_Thread_10ms;
    uint32_t Tick_Thread_100ms;

    //
    // uint32_t SYS_Freq;
    // uint32_t AHB_Freq;
    // uint32_t APB1_Freq;
    // uint32_t APB2_Freq;
} Mcu_t;
extern Mcu_t Mcu;

uint32_t Cal_General_TIM_CLock(void);
void Mcu_Init(void);




#endif
