
#include "../include/libs-hardware.h"
#include <kernel-dvos.h>


static UInt32 memoryModuleNumber;
static UInt32 memoryModuleIndex;
static MemoryModule * memoryModules;

MemProtocolSendCallback sendFromModuleToMaster;


void InitMemoryModule(UInt32 number, MemProtocolSendCallback func)
{
    memoryModuleIndex = 0;
    memoryModuleNumber = number;
    memoryModules = malloc( sizeof(MemoryModule) * number);
    sendFromModuleToMaster = func;
}

void AddMemoryModule(UInt16 virtualAddr, UInt8 * objectAddr, UInt32 objectSize, MemProtocolUpdateCallback update )
{
    memoryModules[memoryModuleIndex].id = virtualAddr;
    memoryModules[memoryModuleIndex].size = objectSize;
    memoryModules[memoryModuleIndex].ptr = objectAddr;
    memoryModules[memoryModuleIndex].update = update;
    
    memoryModuleIndex++;
}

MemoryModule * GetMemoryModuleFromAddress(UInt16 address)
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


void UpdateMemoryModule(UInt8 *buffer, UInt8 size)
{
    UInt32 i ;
    MemoryModule * mem;
    UInt8* ptr;
    UInt32 offset;
    UInt16 virtualAddr;

    virtualAddr = ((buffer)[1]<<8)|((buffer)[0]);

    mem = GetMemoryModuleFromAddress(virtualAddr);

    if ( mem == 0 )
    {
        return;
    }

    offset = virtualAddr - mem->id ;
    ptr     = mem->ptr + offset;

    //DebugPrintf("Addr 0x%x FoundId 0x%x Off %d MSiz %d Size %d\r\n", currentSlaveModAddr, mem->id, offset, mem->size, size );

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
