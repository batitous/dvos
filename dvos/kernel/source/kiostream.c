/*
	Dvos - Copyright © 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard

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