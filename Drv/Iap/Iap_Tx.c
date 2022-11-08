#include "Iap_Tx.h"
#include "App.h"



Iap_Tx_t Iap_Tx = {0};

//////// 数据输出
void Iap_PrintFrame(Iap_Tx_Frame_t *pFrame)
{
    uint32_t Index = 0;


    //////// 准备发送数据
    // 帧头
    Iap_Tx.Buf[Index++] = IAP_UART_HEAD;

    // 地址
    Iap_Tx.Buf[Index++] = pFrame->AddrTx;
    Iap_Tx.Buf[Index++] = pFrame->AddrRx;

    // 指令
    Iap_Tx.Buf[Index++] = pFrame->Cmd;

    // 数据域长度
    Iap_Tx.Buf[Index++] = pFrame->DataLen >> 8;
    Iap_Tx.Buf[Index++] = pFrame->DataLen & 0xFF;

    //////// 数据域
    for (uint32_t i=0; i<pFrame->DataLen; i++)
    {
        Iap_Tx.Buf[Index++] = pFrame->Data[i];
    }

    // CRC8
    //Iap_Tx.Buf[Index] = 0x00;
    Iap_Tx.Buf[Index] = CRC8_Calc(Iap_Tx.Buf + 1, Index - 1);
    Index++;

    //////// 输出
    Iap_PrintArray(Iap_Tx.Buf, Index);
}





//////// 接收数据复制给发送数据 DataLen, Data
void Iap_Copy_Data(Iap_Tx_Frame_t *pTxFrame, Iap_Rx_Frame_t *pRxFrame)
{
    pTxFrame->DataLen = pRxFrame->DataLen;
    for (uint32_t i=0; i<pRxFrame->DataLen; i++)
    {
        pTxFrame->Data[i] = pRxFrame->Data[i];
    }
}

//////// 数据回复
void Iap_Tx_Respond(void)
{
    Iap_Tx_Frame_t *pIap_Tx_Frame = rt_malloc(IAP_TX_FRAME_DATA_BUF_SIZE);

    //////// 复制指令
    pIap_Tx_Frame->AddrTx = Iap_Rx.Frame.AddrRx;
    pIap_Tx_Frame->AddrRx = Iap_Rx.Frame.AddrTx;
    pIap_Tx_Frame->Cmd = Iap_Rx.Frame.Cmd;
    pIap_Tx_Frame->DataLen = 0;



    //////// 准备数据
    switch (Iap_Rx.Frame.Cmd)
    {
        case IapCmd_GotoMode:  // 工作模式跳转
            Iap_Copy_Data(pIap_Tx_Frame, &(Iap_Rx.Frame));
            switch (App.State)
            {
                case AppState_IapTester:
                    pIap_Tx_Frame->Data[0] = 1;
                    break;

                case AppState_IapMcuUpdata:
                    pIap_Tx_Frame->Data[0] = 2;
                    break;

                default:
                    pIap_Tx_Frame->Data[0] = 0;
                    break;
            }
            break;

        // A5 02 01 11 00 0C 46 57 32 30 31 30 2C 30 2E 30 2E 30 EF
        case 0x11:  // 项目号+版本号
        case 0xB2:  // 完成
                pIap_Tx_Frame->DataLen = rt_sprintf((char *)(pIap_Tx_Frame->Data), 
                                                    "%s,%s,%d.%d.%d.%d,%s", 
                                                    PROJECT_NAME, 
                                                    MCU_NAME, 
                                                    BOARD_VERSION_0, 
                                                    BOARD_VERSION_1, 
                                                    BOARD_VERSION_2,
                                                    BOARD_VERSION_3,
                                                    BOARD_BUILD_DATE);
            break;


        // A5 04 02 12 00 00 D7
        case 0x12:  // 读运行数据
            pIap_Tx_Frame->DataLen = sizeof(Run_Data_t);
            {
                Run_Data_t Run_Data = {0};
                //
                Run_Data.Fan_State = Fan.State;
                //Run_Data.Ptc_State = Ptc.State;
                Run_Data.NULL_State = 0;
				        //Run_Data.Dirty_State = Button_Dirty.Dirty_State;


                //////// 复制发送数据
                memcpy(pIap_Tx_Frame->Data, &Run_Data, sizeof(Run_Data_t));
            }
            break;



        //////// 功率器件
        case IapCmd_Fan:
        case IapCmd_Ptc:
            Iap_Copy_Data(pIap_Tx_Frame, &(Iap_Rx.Frame));
            break;


        default:
            break;
    }

    //////// 发送
    Iap_PrintFrame(pIap_Tx_Frame);
    rt_free(pIap_Tx_Frame);
}

//////// 数据请求
void Iap_Tx_Request(void)
{
    Iap_Tx_Frame_t *pIap_Tx_Frame = rt_malloc(IAP_TX_FRAME_DATA_BUF_SIZE);

    //////// 复制指令
    pIap_Tx_Frame->AddrTx = UART_ADDR_BASE;
    pIap_Tx_Frame->AddrRx = UART_ADDR_MAIN;
    pIap_Tx_Frame->Cmd = 0x10;
    pIap_Tx_Frame->DataLen = 11;

    //////// 准备数据
		pIap_Tx_Frame->Data[0] = brush_fan.State;
		pIap_Tx_Frame->Data[1] = brush_heater.State;
		pIap_Tx_Frame->Data[2] = 0;
		pIap_Tx_Frame->Data[3] = Mop.Error;
		
		pIap_Tx_Frame->Data[4] = rubbish_heater.State;
		pIap_Tx_Frame->Data[5] = drain_valve.State;
		pIap_Tx_Frame->Data[6] = magnetic_valve.State;
		pIap_Tx_Frame->Data[7] = peristaltic_pump.State;
		
		pIap_Tx_Frame->Data[8] = rubbish_fan.State;
		pIap_Tx_Frame->Data[9] = Fan.State;
		
		pIap_Tx_Frame->Data[10] = base_module.Base_NTC_Info.ModuleState 
															|(base_module.Trash_Basket_Info.ModuleState << 1)
															|(base_module.Cleaning_Material_Info.ModuleState << 2)
															|(base_module.Trash_Basket_Full_Info.ModuleState << 3);

    //////// 数据输出
    Iap_PrintFrame(pIap_Tx_Frame);
    rt_free(pIap_Tx_Frame);
}
