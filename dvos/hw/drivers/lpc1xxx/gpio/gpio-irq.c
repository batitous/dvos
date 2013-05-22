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


//----------------------------- private functions

extern void keventGpioIrqCallback(UInt32 event, UInt32 edge);

UInt32 getIRQNumber(UInt32 reg)
{
    UInt32 i;
    
    for(i=0;i<31;i++)
    {
        if( ((reg >> i)&0x1) != 0)
        {
            return i;
        }
    }
    return 0;
}

//----------------------------- public functions

void EnableEventOnGpio(GPIO_PIN pin, GPIO_EDGE edge, KEventCallback callback)
{
    // encode the event id with pin, edge and event mask
    if( RegisterEvent( KEVENT_GPIO_MASK | pin /*| edge*/, callback) == False )
    {
        return;
    }
    
    SetGpioIrqCallback(keventGpioIrqCallback);
        
    SetGpioDirection(pin,GPIO_IN);
    EnableGpioIrq(pin,edge);
    
}
