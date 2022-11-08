#ifndef _IAP_TX_H
#define _IAP_TX_H

#include "includes.h"



#define IAP_TX_FRAME_DATA_BUF_SIZE  (100)

typedef struct 
{
    uint8_t AddrTx;
    uint8_t AddrRx;
    uint8_t Cmd;
    uint16_t DataLen;
    uint8_t Data[IAP_TX_FRAME_DATA_BUF_SIZE];
    uint8_t Crc8;
} Iap_Tx_Frame_t;   // 去掉帧头的其他所有部分

typedef struct
{
    // [0 1 2 3]
    uint8_t Brush_State;
    uint8_t Heater_State;
    uint8_t NULL_State;
    uint8_t Mop_ERROR_State;

} Run_Data_t;

typedef struct
{
    bool_t Flag;
    uint8_t Buf[IAP_TX_FRAME_DATA_BUF_SIZE];
} Iap_Tx_t;
extern Iap_Tx_t Iap_Tx;


void Iap_PrintFrame(Iap_Tx_Frame_t *pFrame);

void Iap_Tx_Respond(void);

void Iap_Tx_Request(void);

#endif
