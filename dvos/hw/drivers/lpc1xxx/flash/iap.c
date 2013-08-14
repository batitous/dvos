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




//----------------------------- public functions

Bool iapWriteBuffer(UInt32 flash_address, UInt32 * buffer, UInt32 count)
{
    UInt32 iapParameter[5];
    UInt32 iapResult[5];

    //todo disable irq
    __disable_irq();
    
    iapParameter[0] = IAP_COPY_RAM_TO_FLASH;
    iapParameter[1] = flash_address;
    iapParameter[2] = (UInt32)buffer;
    iapParameter[3] = count;
    iapParameter[4] = IAP_CCLK;
    iapExecute(iapParameter,iapResult);

    //todo enable irq
    __enable_irq();
    
    if(iapResult[0] != IAP_SUCCESS)
    {
        return False;
    }
    return True;
}

Bool iapEraseSector(UInt32 start_sector,UInt32 end_sector)
{
    UInt32 iapParameter[5];
    UInt32 iapResult[5];
    
    iapParameter[0] = IAP_ERASE_SECTOR;
    iapParameter[1] = start_sector;
    iapParameter[2] = end_sector;
    iapParameter[3] = IAP_CCLK;
    iapExecute(iapParameter,iapResult);
    
    if(iapResult[0] != IAP_SUCCESS)
    {
        return False;
    }
    return True;
}

Bool iapPrepareSector(UInt32 start_sector,UInt32 end_sector)
{
    UInt32 iapParameter[5];
    UInt32 iapResult[5];
    
    iapParameter[0] = IAP_PREPARE_SECTOR_FOR_WRITE;
    iapParameter[1] = start_sector;
    iapParameter[2] = end_sector;
    iapParameter[3] = IAP_CCLK;
    iapExecute(iapParameter,iapResult);
    
    if(iapResult[0] != IAP_SUCCESS)
    {
        return False;
    }
    return True;
}

void iapReinvokeBootloader(void)
{
    UInt32 iapParameter[5];
    UInt32 iapResult[5];
    
    iapParameter[0] = IAP_REINVOKE_ISP;
    iapExecute(iapParameter,iapResult);
}
