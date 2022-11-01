#ifndef _IAP_RX_H
#define _IAP_RX_H

#include "includes.h"
#include "Bsp.h"


typedef enum
{
    IapRxState_Head,
    IapRxState_AddrTx,
    IapRxState_AddrRx,
    IapRxState_Cmd,
    IapRxState_DataLenH,
    IapRxState_DataLenL,
    IapRxState_Data,
    IapRxState_Crc8,
} Iap_Rx_State_t;


#define IAP_RX_FRAME_OVERTIME_MAX       (80)         // 字节间隔时间ms

#define IAP_RX_FRAME_DATA_BUF_SIZE      (100)

typedef struct 
{
    uint8_t AddrTx;
    uint8_t AddrRx;
    uint8_t Cmd;
    uint8_t DataLenH;
    uint8_t DataLenL;
    uint8_t Data[IAP_RX_FRAME_DATA_BUF_SIZE];
    uint8_t Crc8;
    uint16_t DataLen;
} Iap_Rx_Frame_t;   // 去掉帧头的其他所有部分

typedef struct
{
    uint32_t Tick;
	uint32_t Beat_Tick;
    uint32_t Index;
    Iap_Rx_State_t State;
    Iap_Rx_Frame_t Frame;

    uint8_t Crc8;
    bool_t FrameFlag;

    //////// Tester
    //uint32_t Tester_Cnt[4];
} Iap_Rx_t;
extern Iap_Rx_t Iap_Rx;

void Iap_Rx_Clear(void);
void Iap_Rx_Byte_Analyze(uint8_t RxByte);
void IapHeatBase_Rx_Frame_Analyze(void);

void Iap_Rx_Frame_Analyze(void);
void HeatBase_Rx_Frame_Analyze(void);


#endif
