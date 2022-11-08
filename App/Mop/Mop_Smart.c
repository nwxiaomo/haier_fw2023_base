#include "Mop_Smart.h"
#include "Mop.h"
#include "Drv.h"


// 智能模式
void Mop_Smart(void)
{
    switch (Dirtliness.Level)
    {
        case 0:
            Inhale_Level_Set(InhaleLevel_0_90W);
            Valve_Mode_Set(ValveMode_Alternate_Off);
            break;

        case 1:
            Inhale_Level_Set(InhaleLevel_0_90W);
            Valve_Mode_Set(ValveMode_Alternate_2sOn_3sOff);
            break;

        case 2:
            Inhale_Level_Set(InhaleLevel_2_120W);
            Valve_Mode_Set(ValveMode_Alternate_3sOn_2sOff);
            break;

        case 3:
            Inhale_Level_Set(InhaleLevel_2_120W);
            Valve_Mode_Set(ValveMode_Alternate_8sOn_2sOff);
            break;

        case 4:
            Inhale_Level_Set(InhaleLevel_3_150W);
            Valve_Mode_Set(ValveMode_Alternate_8sOn_2sOff);
            break;

        default:
            break;
    }


    // 流量，前6s，100mL
    if (Mop.Tick_ms < ELAPSE_s(6))
    {
        Pump1_Level_Set(PumpLevel_5);
    }
    else
    {
        switch (Dirtliness.Level)
        {
            case 0:
                Pump1_Level_Set(PumpLevel_0);
                break;

            case 1:
                Pump1_Level_Set(PumpLevel_1);
                break;

            case 2:
                Pump1_Level_Set(PumpLevel_2);
                break;

            case 3:
                Pump1_Level_Set(PumpLevel_3);
                break;

            case 4:
                Pump1_Level_Set(PumpLevel_4);
                break;

            default:
                break;
        }
    }
}


// 除菌模式
void Mop_Degerming(void)
{
    switch (Mop.Mode_Step)
    {
        case 0:     // Start
            Mop.Mode_Tick = 0;
            Mop.Mode_Step++;
            //
            Electrolyze_Start(ElectrolyzeMode_Only_8min);
            break;

        case 1:     // 电解水
            switch (Mop.Mode_Tick)
            {
                case 0:
                    WT588_Speak(VOICE_CMD_Disinfecting);
                    break;

                case (ELAPSE_s(10) / 2):
                    WT588_Speak(VOICE_CMD_DisinfectHalf);
                    break;

                case (ELAPSE_s(10) - ELAPSE_ms(1500)):
                    WT588_Speak(VOICE_CMD_Disinfected);
                    break;

                default:
                    break;
            }


            Mop.Mode_Tick++;
            if (Mop.Mode_Tick >= ELAPSE_s(10))
            {
                Mop.Mode_Tick = 0;
                Mop.Mode_Step++;
                //
                Inhale_Start(0);
                Brush_Start(BrushProtectMode_Mop);
                Dirtliness_Start();
                if (0 == Mop.Warning_TankClearEmpty)
                {
                    Pump1_Start(PumpLevel_0, ValveMode_On);
                }
                //WT588_Speak(VOICE_CMD_SmartMode);
            }
            break;

        case 2:     // 智能模式
            Mop_Smart();
            break;

        default:
            break;
    }
}
