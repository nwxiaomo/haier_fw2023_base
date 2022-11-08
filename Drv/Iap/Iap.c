#include "Iap.h"
#include "App.h"


Iap_t Iap = {0};



void Iap_Init(void)
{
	// 设置地址信息
    //Comm_PrintFrame_0x10();

	// 打印信息：项目名，芯片名，版本号，编译日期
    rt_kprintf("Comm_Init: %s,%s,%d.%d.%d.%d,%s\r\n", 
                PROJECT_NAME, 
                MCU_NAME, 
                BOARD_VERSION_0, 
                BOARD_VERSION_1, 
                BOARD_VERSION_2,
                BOARD_VERSION_3,
                BOARD_BUILD_DATE);
}

//////// 设置地址信息
void Iap_PrintFrame_0x10(void)
{
    Iap_Rx.Frame.AddrTx = 0x06;
    Iap_Rx.Frame.AddrRx = 0x02;
    Iap_Rx.Frame.Cmd = 0x10;
}


// 1ms
void Iap_Task(void)
{
	//////// App状态
    switch (App.State)
    {
        case AppState_IapTester:   // 关定时发送数据
        case AppState_IapMcuUpdata: 
            break;

        default:                    // 开始定时发送数据
			//////// Tx
			Iap.Tick++;
			if (Iap.Tick >= IAP_ASK_FRAME_SENDTIME)
			{
				Iap.Tick = 0;
				Iap_Tx_Request();
			}
			/* 
			if (Comm_Tx.Flag)
			 {
				 Comm_Tx.Flag = 0;
				 //
				 
			 }
			*/
            break;
    }


    //////// Rx 
    if (Iap_Rx.Tick < IAP_RX_FRAME_OVERTIME_MAX)
    {
        Iap_Rx.Tick++;
        if (Iap_Rx.Tick >= IAP_RX_FRAME_OVERTIME_MAX)
        {
            Iap_Rx_Clear();			
        }
    }
	
	//////// 通讯心跳检查 
    if (Iap_Rx.Beat_Tick < IAP_Beat_OVERTIME_MAX)
    {
        Iap_Rx.Beat_Tick++;
        if (Iap_Rx.Beat_Tick >= IAP_Beat_OVERTIME_MAX)
        {
            rt_mb_send(mb_AppEvent, AppEvent_Comm_Disconnect);			
        }
    }
	

    if (Iap_Rx.FrameFlag)
    {
        Iap_Rx.FrameFlag = 0;
        //解析接收到的数据
        IapHeatBase_Rx_Frame_Analyze();
    }


    //////// Test
    //Iap.Test_Cnt++;
}
