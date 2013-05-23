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

//--------------------- private functions:

static Bool executeEepromCommand(UInt32 command, UInt32 addr, UInt8 * buffer, UInt32 size)
{
    UInt32 param[5];
    UInt32 result[4];
    
    param[0] = command;
    param[1] = addr;
    param[2] = (UInt32)buffer;
    param[3] = size;
    param[4] = IAP_CCLK;
    iapExecute(param,result);
    
    if(result[0] != IAP_SUCCESS)
    {
        return False;
    }
    
    return True;
}

//--------------------- public functions:

Bool readByteFromEeprom(UInt32 addr, UInt8* data)
{
    return executeEepromCommand(IAP_READ_EEPROM,addr,data,1);
}

Bool readBufferFromEeprom(UInt32 addr, UInt8* buffer, UInt32 size)
{
    return executeEepromCommand(IAP_READ_EEPROM,addr,buffer,size);
}


Bool writeByteToEeprom(UInt32 addr, UInt8 data)
{
    return executeEepromCommand(IAP_WRITE_EEPROM,addr,&data,1);
}

Bool writeBufferToEeprom(UInt32 addr, UInt8* buffer, UInt32 size)
{
    return executeEepromCommand(IAP_WRITE_EEPROM,addr,buffer,size);
}

Bool eraseEeprom()
{
    return False;
}

