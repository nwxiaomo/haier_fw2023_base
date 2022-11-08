#ifndef _COMM_H
#define _COMM_H

#include "includes.h"
#include "Bsp.h"

#include "Iap_Tx.h"
#include "Iap_Rx.h"


#define IAP_UART_HEAD       (0xA5)

//#define IAP_ASK_FRAME_SENDTIME       (200)						// 请求帧发送时间ms

#define IAP_ASK_FRAME_SENDTIME       (200)						// 请求帧发送时间ms
#define IAP_Beat_OVERTIME_MAX       (IAP_ASK_FRAME_SENDTIME*5)	// 字节间隔时间ms

#define HeatBaseCmd_Operate 0x10								// 烘干底座操作命令

typedef enum
{
    //////// 
	IapCmd_GotoMode     = 0x10, // 工作模式跳转     0)正常模式，1)测试机模式
    IapCmd_ReadProject  = 0x11, // 读项目号+版本号


    // 功率器件
		IapCmd_Brush_Fan      	= 0x40, // 风扇
    IapCmd_Brush_Heater			= 0x41, // PTC
		
	
	
	
} Comm_Cmd_t;


typedef enum
{
    CommState_Stop,
    CommState_Run,
} Comm_State_t;


typedef struct
{
    uint32_t Tick;
    Comm_State_t State;

    //////// Test
    //uint32_t Test_Cnt;
} Iap_t;
extern Iap_t Iap;


void Iap_Init(void);

void Iap_PrintFrame_0x10(void);

void Iap_Task(void);


#endif
