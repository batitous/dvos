/*
	Dvos - Copyright (C) 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard

    This file is part of Dvos.

    Dvos is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Dvos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "../include/libs-hardware.h"


#define SUPPLY_CMD      GPIO0_8
#define ISENSE_OUT      ANA3
#define VSENSE_OUT      ANA2

// Wakeup pin P0.22


void setMainPowerSupply(Bool enable)
{
    //Supply pin P0.8

    setGpioDirection(SUPPLY_CMD,GPIO_OUT);
    
    
    if(enable==True)
    {
        setGpioValue(SUPPLY_CMD,1);
    }
    else
    {
        setGpioValue(SUPPLY_CMD,0);
    }
    
}

UInt32 getBatteryVoltage(void)
{
    // Vbattery = Vana / 0.2769
    
    
    // Analog : 12 bits = 3.3V = 4096
    // 1 mV = 1.24
    
    // 1 ana = 0.8 mV
    
    // 1 ana = 2.91 vbatt
    
    UInt32 battery = (UInt32) getMcuAnalog(VSENSE_OUT);
    
//    DebugPrintf("Ana2 = %d\r\n", battery);
    
    battery = (battery * 290) / 100;
    
    return battery;
}

UInt32 getCurrentConsumption(void)
{
    // 1 A = 1.2 V
    
    // 1.2mV = 1.4 ana
    
    // 1 ana = 0.714 mA
    
    
    UInt32 current = (UInt32) getMcuAnalog(ISENSE_OUT);
    
//    DebugPrintf("Current (ana1) = %d\r\n", current);
    
    return (current * 71) / 100;
}

