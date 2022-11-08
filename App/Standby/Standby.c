#include "Standby.h"


Standby_t Standby = {0};


void Standby_Start(void)
{
    Standby.Tick = 0;
}

void Standby_Stop(void)
{
    
}


// 1ms
void Standby_Task(void)
{

}
