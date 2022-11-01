#include "Iap.h"
#include "App.h"


Iap_t Iap = {0};



void Iap_Init(void)
{
	// ??????
    //Comm_PrintFrame_0x10();

	// ????:???,???,???,????
    rt_kprintf("Comm_Init: %s,%s,%d.%d.%d.%d,%s\r\n", 
                PROJECT_NAME, 
                MCU_NAME, 
                BOARD_VERSION_0, 
                BOARD_VERSION_1, 
                BOARD_VERSION_2,
                BOARD_VERSION_3,
                BOARD_BUILD_DATE);
}

//////// ??????
void Iap_PrintFrame_0x10(void)
{
    Iap_Rx.Frame.AddrTx = 0x06;
    Iap_Rx.Frame.AddrRx = 0x02;
    Iap_Rx.Frame.Cmd = 0x10;
}


// 1ms
void Iap_Task(void)
{
	//////// App??
    switch (App.State)
    {
        case AppState_IapTester:    // ???????
        case AppState_IapMcuUpdata: 
            break;

        default:                    // ????????
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
	
	//////// ?????? 
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
        //????????
        IapHeatBase_Rx_Frame_Analyze();
    }


    //////// Test
    //Iap.Test_Cnt++;
}
