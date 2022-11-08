#include "UserMain.h"
#include "Thread.h"


rt_sem_t sem_UserTick_1ms;      // 信号量，1ms时钟

uint8_t  read_data = 0;
void UserMain(void)
{
    sem_UserTick_1ms = rt_sem_create("tick1ms", 0, RT_IPC_FLAG_FIFO);
	
		Log_Init();
    //////// Bsp
		Bsp_Init();

    //////// Drv
    Drv_Init();

    //////// App
    App_Init();

    //////// Start ////////
    Bsp_Start();

    for (;;)
    {
        rt_sem_take(sem_UserTick_1ms, RT_WAITING_FOREVER);

        //Interval_Start();

        //////// Bsp
        Bsp_Task();

        //////// Drv
        Drv_Task();

        //////// App
        App_Task();

        //////// Tick ////////
        // 1ms
        Mcu.Tick_ms = U32_Add_One(Mcu.Tick_ms);
        Mcu.Tick_Loop_1ms++;
        // 10ms
        if (Mcu.Tick_Loop_10ms < 10 - 1)
        {

            Mcu.Tick_Loop_10ms++;
        }
        else
        {
            Mcu.Tick_Loop_10ms = 0;
        }

        // 100ms
        if (Mcu.Tick_Loop_100ms < 100 - 1)
        {
            Mcu.Tick_Loop_100ms++;
        }
        else
        {
            Mcu.Tick_Loop_100ms = 0;
        }

        // 1000ms
        if (Mcu.Tick_Loop_1000ms < 1000 - 1)
        {
            Mcu.Tick_Loop_1000ms++;
        }
        else
        {
            Mcu.Tick_Loop_1000ms = 0;
            //
            App.Tick_s = U32_Add_One(App.Tick_s);

            if (Mcu.Tick_Loop_3s < 3-1)
            {
                Mcu.Tick_Loop_3s++;
            }
            else
            {
								LOG_DEB("user main running........");
                Mcu.Tick_Loop_3s = 0;
                
            }
            
        }

        //Interval_Stop();
    }
}
