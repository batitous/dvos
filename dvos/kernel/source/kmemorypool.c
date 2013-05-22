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
#include "../../hw/include/libs-default.h"
#include "../include/kernel-dvos.h"


//----------------------------- debug

//#define MEMPOOL_USE_DEBUG

#ifdef MEMPOOL_USE_DEBUG
#   define TRACE_MEMPOOL(str)	DebugPrintf str
#else
#   define TRACE_MEMPOOL(str)
#endif

//----------------------------- private variables

static UInt8 * nextPoolFreeAddress;
static UInt8 * lastPoolAddress;

//----------------------------- public functions

void initMemoryPool(UInt8 * address, UInt32 size)
{
    nextPoolFreeAddress = address;
    lastPoolAddress = nextPoolFreeAddress + size;
    
    TRACE_MEMPOOL(("mempool init at 0x%x size %d\r\n", address, size)); 
}

void * getMemoryPool(UInt32 size)
{
    UInt8 * currentPool = nextPoolFreeAddress;
    
    if( (nextPoolFreeAddress+size) <= lastPoolAddress)
    {
        nextPoolFreeAddress += size;
     
        TRACE_MEMPOOL(("mempool alloc at 0x%x size %d\r\n", currentPool,size));
        
        return (void *)currentPool;
    }
    
    TRACE_MEMPOOL(("mempool full ! next 0x%x last 0x%x\r\n", nextPoolFreeAddress, lastPoolAddress));
    
    return 0;
}
