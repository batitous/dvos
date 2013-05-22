
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
