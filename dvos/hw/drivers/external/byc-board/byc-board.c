
#include "../include/libs-hardware.h"


#define SUPPLY_CMD      GPIO0_8
#define ISENSE_OUT      ANA3
#define VSENSE_OUT      ANA2

// Wakeup pin P0.22


void SetMainPowerSupply(Bool enable)
{
    //Supply pin P0.8

    SetGpioDirection(SUPPLY_CMD,GPIO_OUT);
    
    
    if(enable==True)
    {
        SetGpioValue(SUPPLY_CMD,1);
    }
    else
    {
        SetGpioValue(SUPPLY_CMD,0);
    }
    
}

UInt32 GetBatteryVoltage(void)
{
    // Vbattery = Vana / 0.2769
    
    
    // Analog : 12 bits = 3.3V = 4096
    // 1 mV = 1.24
    
    // 1 ana = 0.8 mV
    
    // 1 ana = 2.91 vbatt
    
    UInt32 battery = (UInt32) GetMcuAnalog(VSENSE_OUT);
    
//    DebugPrintf("Ana2 = %d\r\n", battery);
    
    battery = (battery * 290) / 100;
    
    return battery;
}

UInt32 GetCurrentConsumption(void)
{
    // 1 A = 1.2 V
    
    // 1.2mV = 1.4 ana
    
    // 1 ana = 0.714 mA
    
    
    UInt32 current = (UInt32) GetMcuAnalog(ISENSE_OUT);
    
//    DebugPrintf("Current (ana1) = %d\r\n", current);
    
    return (current * 71) / 100;
}

