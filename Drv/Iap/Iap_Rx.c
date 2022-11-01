#include "Iap_Rx.h"
#include "App.h"


Iap_Rx_t Iap_Rx = {0};

void HeatBase_Rx_Frame_Analyze(void);

void Iap_Rx_Clear(void)
{
    Iap_Rx.State = IapRxState_Head;
}

//////// RX接收状态机
void Iap_Rx_Byte_Analyze(uint8_t RxByte)
{
    Iap_Rx.Tick = 0;

    switch (Iap_Rx.State)
    {
        case IapRxState_Head:
            if (RxByte != IAP_UART_HEAD)
            {
                Iap_Rx_Clear();
            }
            else
            {
                Iap_Rx.State = IapRxState_AddrTx;
            }
            break;

        case IapRxState_AddrTx:
            Iap_Rx.Frame.AddrTx = RxByte;
            Iap_Rx.State = IapRxState_AddrRx;
            break;

        case IapRxState_AddrRx:
            Iap_Rx.Frame.AddrRx = RxByte;
            Iap_Rx.State = IapRxState_Cmd;
            break;

        case IapRxState_Cmd:
            Iap_Rx.Frame.Cmd = RxByte;
            Iap_Rx.State = IapRxState_DataLenH;
            break;


        case IapRxState_DataLenH:
            Iap_Rx.Frame.DataLenH = RxByte;
            Iap_Rx.Frame.DataLen = RxByte * 0x100;
            Iap_Rx.State = IapRxState_DataLenL;
            break;

        case IapRxState_DataLenL:
            Iap_Rx.Frame.DataLenL = RxByte;
            Iap_Rx.Frame.DataLen += RxByte; // 计算总长度
			if (Iap_Rx.Frame.DataLen == 0)	 // 判断长度是否为0
            {
                Iap_Rx.State = IapRxState_Crc8;
            }
            else if (Iap_Rx.Frame.DataLen <= IAP_RX_FRAME_DATA_BUF_SIZE)	// 长度合适
            {
                Iap_Rx.Index = 0;
                Iap_Rx.State = IapRxState_Data;
            }
            else // 长度过大
            {
                Iap_Rx_Clear();
            }
            break;

        case IapRxState_Data:
            Iap_Rx.Frame.Data[Iap_Rx.Index++] = RxByte;
            if (Iap_Rx.Index == Iap_Rx.Frame.DataLen)
            {
                Iap_Rx.State = IapRxState_Crc8;
            }
            break;

        case IapRxState_Crc8:
            Iap_Rx.Frame.Crc8 = RxByte;
            Iap_Rx.FrameFlag = 1;
            Iap_Rx_Clear();
            break;

        default:
            break;
    }
}


//////// 数据解析
void IapHeatBase_Rx_Frame_Analyze(void)
{	
    //////// 验证 CRC8
    Iap_Rx.Crc8 = CRC8_Calc(&Iap_Rx.Frame.AddrTx, (Iap_Rx.Frame.DataLen + 5));
    if ((Iap_Rx.Frame.Crc8 != Iap_Rx.Crc8) && (Iap_Rx.Frame.Crc8 != 0x00))
    {
        //rt_kprintf("RxFrame Crc8 Error\r\n");
        return;
    }
	
    //////// 验证地址
    if ((Iap_Rx.Frame.AddrTx == UART_ADDR_PC) && (Iap_Rx.Frame.AddrRx == UART_ADDR_BASE))
    {
        Iap_Rx_Frame_Analyze();
    }
    else if ((Iap_Rx.Frame.AddrTx == UART_ADDR_MAIN) && (Iap_Rx.Frame.AddrRx == UART_ADDR_BASE))
    {
        HeatBase_Rx_Frame_Analyze();
    }
    else
    {
        return;
    }
	
	Iap_Rx.Beat_Tick = 0;

}

void Iap_Rx_Frame_Analyze(void)
{
    //////// App状态
    switch (App.State)
    {
        case AppState_IapTester:    // 不响应更新
            if (Iap_Rx.Frame.Cmd >= 0xB0)
            {
                return;
            }
            break;

        case AppState_IapMcuUpdata: // 响应全部内容
            break;

        default:                    // 不响应测试机和更新
            if (Iap_Rx.Frame.Cmd != IapCmd_GotoMode)
            {
                return;
            }
            break;
    }

    //////// 命令
    switch (Iap_Rx.Frame.Cmd)
    {
        // A5 04 06  10  00 01  00  00      // 进入用户模式
        // A5 04 06  10  00 01  01  00      // 进入测试模式
        // A5 04 06  10  00 01  02  00      // 进入更新模式
        case IapCmd_GotoMode:  // 工作模式跳转
            if (Iap_Rx.Frame.DataLen < 1)
            {
                return;
            }

            switch (Iap_Rx.Frame.Data[0])
            {
                case 0x00:
                    rt_mb_send(mb_AppEvent, AppEvent_Iap_GotoUser);
                    break;

                case 0x01:
                    rt_mb_send(mb_AppEvent, AppEvent_Iap_GotoTester);
                    break;

                case 0x02:
                    //rt_mb_send(mb_AppEvent, AppEvent_Iap_GotoMcuUpdata);
                    break;

                default:
                    break;
            }
            break;

        // A5 04 06 11 00 00 00      // 读项目号
        case 0x11:  // 项目号+版本号
            Iap_Tx_Respond();
            break;

        // A5 04 02 12 00 00 D7 
        case 0x12:  // 读运行数据
            Iap_Tx_Respond();
            break;
		
        case IapCmd_Fan:
            if (Iap_Rx.Frame.DataLen < 2)
            {
                 return;
            }

            // Data[0]  电机编号
            // Data[1]  档位编号
            switch (Iap_Rx.Frame.Data[0])
            {
                case 0:     // 前部水泵
                    switch (Iap_Rx.Frame.Data[1])
                    {
                        case 0x00:  // 关闭
                            Fan_Stop();
                            break;

                        default:    // 打开
                            Fan_Start();
                            break;
                    }
                    break;

                default:
                    break;
            }
            Iap_Tx_Respond();
            break;
		
        case IapCmd_Ptc:
            if (Iap_Rx.Frame.DataLen < 2)
            {
                 return;
            }

            // Data[0]  电机编号
            // Data[1]  档位编号
            switch (Iap_Rx.Frame.Data[0])
            {
                case 0:     // 前部水泵
                    switch (Iap_Rx.Frame.Data[1])
                    {
                        case 0x00:  // 关闭
                            //Ptc_Stop();
                            break;

                        default:    // 打开
                            //Ptc_Start();
                            break;
                    }
                    break;

                default:
                    break;
            }
            Iap_Tx_Respond();
            break;

        default:
            break;
    }
}
void HeatBase_Rx_Frame_Analyze(void)
{
    //////// 
    switch (Iap_Rx.Frame.Cmd)
    {			
        case HeatBaseCmd_Operate:  // 执行命令
            if (Iap_Rx.Frame.DataLen < 1)
            {
                return;
            }
						
			      // 风机
            switch (Iap_Rx.Frame.Data[0])
            {
                case 0x00:
                    Fan_Stop();
                    break;

                case 0x01:
										switch (Mop.State)
										{
											case MopState_Run:
												Fan_Start();
												break;
											default:
												break;
										}
										break;

                default:
                    break;
            }
			     // PTC
            switch (Iap_Rx.Frame.Data[1])
            {
                case 0x00:
                    Brush_Heater_Stop();
                    break;

                case 0x01:
									switch (Mop.State)
									{
										case MopState_Run:
											Brush_Heater_Start();
											break;

										default:
											break;
									}
                  break;

                default:
                  break;
            }
						
            switch (Iap_Rx.Frame.Data[3])
            {
                case 0x00:
									Rubbish_Heater_Stop();
                  break;

                case 0x01:
									switch (Mop.State)
									{
										case MopState_Run:
											Rubbish_Heater_Start();
											break;

										default:
											break;
									}
                  break;

                default:
                  break;
            }
						
						switch (Iap_Rx.Frame.Data[4])
            {
                case 0x00:
									Drain_Valve_Stop();
                  break;

                case 0x01:
									switch (Mop.State)
									{
										case MopState_Run:
											Drain_Valve_Start();
											break;

										default:
											break;
									}
                  break;

                default:
                  break;
            }
						
						switch (Iap_Rx.Frame.Data[5])
            {
                case 0x00:
									Magnetic_Valve_Stop();
                  break;

                case 0x01:
									switch (Mop.State)
									{
										case MopState_Run:
											Magnetic_Valve_Start();
											break;

										default:
											break;
									}
                  break;

                default:
                  break;
            }
						
						switch (Iap_Rx.Frame.Data[6])
            {
                case 0x00:
									Peristaltic_Pump_Stop();
                  break;

                case 0x01:
									switch (Mop.State)
									{
										case MopState_Run:
											Peristaltic_Pump_Start();
											break;

										default:
											break;
									}
                  break;

                default:
                  break;
            }
						
						switch (Iap_Rx.Frame.Data[7])
            {
                case 0x00:
									Rubbish_Fan_Stop();
                  break;

                case 0x01:
									switch (Mop.State)
									{
										case MopState_Run:
											Rubbish_Fan_Start();
											break;

										default:
											break;
									}
                  break;

                default:
                  break;
            }
						
						switch (Iap_Rx.Frame.Data[7])
            {
                case 0x00:
									Brush_Fan_Stop();
                  break;

                case 0x01:
									switch (Mop.State)
									{
										case MopState_Run:
											Brush_Fan_Start();
											break;

										default:
											break;
									}
                  break;

                default:
                  break;
            }
			
						rt_mb_send(mb_AppEvent, AppEvent_Comm_Connect);
            break;


        default:
            break;
    }
}