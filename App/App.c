#include "App.h"


App_t App = {0};


void App_Init(void)
{
	// 创建邮箱
    mb_AppEvent = rt_mb_create("App", 3, RT_IPC_FLAG_FIFO);
}


void App_Task(void)
{
    //////// Event
    rt_ubase_t mbVaule_AppEvent;
    if (RT_EOK == rt_mb_recv(mb_AppEvent, &mbVaule_AppEvent, 0))
    {
        switch (mbVaule_AppEvent)
        {
            //////// 通讯连接
            case AppEvent_Comm_Connect:
                Comm_Connect_Event();
                break;
            //////// 通讯断开连接
            case AppEvent_Comm_Disconnect:
                Comm_Disconnect_Event();
                break;
			
            //////// 运行动作
            case AppEvent_Goto_Standby:
                Goto_Standby_Event();
                break;

			//////// Iap
            case AppEvent_Iap_GotoUser:
                Iap_GotoUser_Event();
                break;

            case AppEvent_Iap_GotoHalt:
                Iap_GotoHalt_Event();
                break;

            case AppEvent_Iap_GotoTester:
                Iap_GotoTester_Event();
                break;

            case AppEvent_Iap_GotoMcuUpdata:
                Iap_GotoMcuUpdata_Event();
                break;
			
            default:
                break;
        }
    }

    //////// 
    switch (App.State)
    {
        case AppState_Start:
            break;

        case AppState_Standby:
            //Standby_Task();
            break;

        case AppState_Mop:
            Mop_Task();
            break;

        case AppState_IapTester:
            IapTester_Task();
            break;

        case AppState_IapMcuUpdata:
            //IapMcuUpdata_Task();
            break;

        default:
            break;
    }
}


void AppState_Goto(App_State_t NewState)
{
    if (NewState == App.State)
    {
		return;
    }
	
    // 保存旧状态
    App.State_Last = App.State;


    //////// 关闭旧状态
    switch (App.State)
    {
        case AppState_Standby:
            //Standby_Stop();
            break;

        case AppState_Halt:
            //Halt_Stop();
            break;

        case AppState_Mop:
            Mop_Stop();
            break;

        case AppState_IapTester:
            IapTester_Stop();

        case AppState_IapMcuUpdata:
            
            break;

        default:
            break;
    }



    //////// 开启新状态
    switch (NewState)
    {
        case AppState_Standby:
            //Standby_Start();
            break;

        case AppState_Halt:
            //Halt_Start();
            break;

        case AppState_Mop:
            Mop_Start();
            break;

        case AppState_IapTester:
            IapTester_Start();
            break;

        case AppState_IapMcuUpdata:
            
            break;

        default:
            break;
    }

    //////// 切换状态
    App.State = NewState;
}






