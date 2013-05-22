
#include "../../hw/include/libs-default.h"

#include "../include/kmemory.h"
#include "../include/klist.h"
#include "../include/kthread.h"
#include "../include/kevent.h"
#include "../include/ktimer.h"
#include "../include/kiostream.h"

#include "../include/kernel-private.h"

#ifdef KERNEL_USE_DEBUG
void dumpIOStream(KIOStream * stream)
{
    DebugPrintf("== io stream: read %d write %d\r\n",stream->read,stream->write);
    DebugPrintf("== io th %x buf %x\r\n",stream->receiver,stream->buffer);
}
#endif

KIOStream * newInputOutputStream(UInt32 size)
{
    KIOStream * result = malloc( sizeof(KIOStream) );
    if(result==0)
    {
        return 0;
    }

    result->read = 0;
    result->write = 0;
    result->receiver = 0;

    result->buffer = malloc( size );
    if(result->buffer==0)
    {
        return 0;
    }
    result->size = size;

    return result;
}

void setByteToStream(KIOStream * stream, UInt8 data)
{
    stream->buffer[stream->write & (stream->size-1)] = data;
    stream->write++;
}

void irqWakeUpTaskFromStream(KIOStream * stream)
{
    KThread * th = stream->receiver;
    
    if(th!=0)
    {
        // a task is waiting, wakeup this task !
        stream->receiver = 0;
        irqSetTaskAsReady(th);
    }
}

UInt32 getAllBufferFromStream(KIOStream * stream, UInt8 * buffer, UInt32 len)
{
    UInt32 counter, i, size;

    size = stream->write;
    if(size==stream->read)
    {
        return 0;
    }
    
    
    
    
    for( i = stream->read, counter = 0 ; i != size && counter<len ; counter++ )
    {
        buffer[counter] = stream->buffer[i & (stream->size-1)];
        i++;        
    }
    stream->read = i;
    
    return counter;
}

Bool getBufferFromStream(KIOStream * stream, UInt8 * buffer, UInt32 len, UInt32 timeout)
{
    UInt32 counter, i;

    for( i = stream->read, counter = 0; counter < len; counter++)
    {
        if(i==stream->write)
        {
            // we don't have enough data, we have to wait some times...
            //stream->receiver = (KThread *)currentTask;
            
            stream->receiver = 0;
            waitMs(timeout);
//            waitUs(timeout*100);
            if(i==stream->write)
            {
                // Timeout !
                return False;
            }

        }

        buffer[counter] = stream->buffer[i & (stream->size-1)];
        i++;
    }

    stream->read = i;

    return True;
}

Bool getByteFromStream(KIOStream * stream, UInt8 * data)
{
    if(stream->read!=stream->write)
    {
        *data = stream->buffer[stream->read & (stream->size-1)];
        stream->read++;
        return True;
    }

    return False;
}

void waitDataFromStream(KIOStream * stream)
{
    if( stream->read==stream->write)
    {
        stream->receiver = (KThread *)currentTask;
        setTaskAsBlocked();
    }
}

Bool isDataAvailableFromStream(KIOStream * stream)
{
    if(stream->read!=stream->write)
    {
        return True;
    }
    
    return False;
}