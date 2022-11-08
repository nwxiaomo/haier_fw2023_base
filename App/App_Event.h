#ifndef _APP_EVENT_H
#define _APP_EVENT_H

#include "includes.h"
//#include "Drv.h"


extern rt_mailbox_t mb_AppEvent;


typedef enum
{
	AppEvent_Comm_Connect,
	AppEvent_Comm_Disconnect,
	
	AppEvent_Iap_GotoHalt,
	AppEvent_Iap_GotoUser,
	AppEvent_Iap_GotoTester,
	AppEvent_Iap_GotoMcuUpdata,

	AppEvent_Goto_Standby,
    //
} App_Event_t;


void Comm_Connect_Event(void);

void Comm_Disconnect_Event(void);

void Goto_Standby_Event(void);


// 需要应答
void Iap_GotoUser_Event(void);
void Iap_GotoHalt_Event(void);
void Iap_GotoTester_Event(void);
void Iap_GotoMcuUpdata_Event(void);

#endif
