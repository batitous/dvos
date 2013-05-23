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
#include <kernel-dvos.h>


static UInt32 memoryModuleNumber;
static UInt32 memoryModuleIndex;
static MemoryModule * memoryModules;

MemProtocolSendCallback sendFromModuleToMaster;


void initMemoryModule(UInt32 number, MemProtocolSendCallback func)
{
    memoryModuleIndex = 0;
    memoryModuleNumber = number;
    memoryModules = malloc( sizeof(MemoryModule) * number);
    sendFromModuleToMaster = func;
}

void addMemoryModule(UInt16 virtualAddr, UInt8 * objectAddr, UInt32 objectSize, MemProtocolUpdateCallback update )
{
    memoryModules[memoryModuleIndex].id = virtualAddr;
    memoryModules[memoryModuleIndex].size = objectSize;
    memoryModules[memoryModuleIndex].ptr = objectAddr;
    memoryModules[memoryModuleIndex].update = update;
    
    memoryModuleIndex++;
}

MemoryModule * getMemoryModuleFromAddress(UInt16 address)
{
    UInt32 i;
    MemoryModule * mem;

    for(i=0; i<memoryModuleNumber; i++)
    {
        mem = &memoryModules[i];
        if( address >= mem->id && address <= mem->id + mem->size)
        {
            return mem;
        }
    }

    return 0;
}


void updateMemoryModule(UInt8 *buffer, UInt8 size)
{
    UInt32 i ;
    MemoryModule * mem;
    UInt8* ptr;
    UInt32 offset;
    UInt16 virtualAddr;

    virtualAddr = ((buffer)[1]<<8)|((buffer)[0]);

    mem = getMemoryModuleFromAddress(virtualAddr);

    if ( mem == 0 )
    {
        return;
    }

    offset = virtualAddr - mem->id ;
    ptr     = mem->ptr + offset;

    //debugPrintf("Addr 0x%x FoundId 0x%x Off %d MSiz %d Size %d\r\n", currentSlaveModAddr, mem->id, offset, mem->size, size );

    if ( size == 2)
    {
        // If we have just 2 bytes of data, then it's a futur read order: 
        // Copy data from memory module to the master:
        sendFromModuleToMaster(virtualAddr, ptr, mem->size - offset);
    }
    else
    {    
        
        // Copy data to memory
        for (i=0; i < (UInt32)(size-2) && i < mem->size ;i++)
        {
            ptr[i] = buffer[i+2];
        }

        // Update the memory module
        if (mem->update!=0)
        {
            mem->update();
        }
    }

}
