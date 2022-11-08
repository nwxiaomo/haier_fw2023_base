#include "Boot.h"


static int Boot_Init(void)
{
    NVIC_Vector_Table_Set(FLASH_BASE, 0x2200);	// 设置偏移量
    return 0;
}
//INIT_BOARD_EXPORT(Boot_Init);
