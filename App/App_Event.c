#include "App_Event.h"
#include "App.h"


rt_mailbox_t mb_AppEvent;



// 通讯应答
void Comm_Connect_Event(void)
{
	  LOG_DEB("The connect event has trigger.");
    switch (App.State)
    {
        case AppState_Start:
        case AppState_Standby:
        case AppState_Halt:
            AppState_Goto(AppState_Mop);
            break;

        case AppState_Mop:        
            break;

        default:
            break;
    }
}

// 通讯断开
void Comm_Disconnect_Event(void)
{
	  LOG_DEB("The disconnect event has trigger.");
    switch (App.State)
    {
        case AppState_Mop:
            switch (Mop.State)
            {
                case MopState_Run:
				case MopState_Shut:
                    Mop_Shut();
                    break;
				
                default:
                    break;
            }          
            break;

        default:
            break;
    }
}

void Goto_Standby_Event(void)
{
		LOG_DEB("The goto standby event has trigger.");
    AppState_Goto(AppState_Standby);
}

// 需要应答
void Iap_GotoUser_Event(void)
{
	AppState_Goto(AppState_Standby);
    Iap_Tx_Respond();
}

void Iap_GotoHalt_Event(void)
{
    AppState_Goto(AppState_Halt);
    Iap_Tx_Respond();
}

void Iap_GotoTester_Event(void)
{
    AppState_Goto(AppState_IapTester);
    Iap_Tx_Respond();
}

void Iap_GotoMcuUpdata_Event(void)
{
//    AppState_Goto(AppState_IapMcuUpdata);
//    Iap_Tx_Respond();
}


