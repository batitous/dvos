
#include "../../hw/include/libs-default.h"

#include "../include/kmemory.h"
#include "../include/klist.h"
#include "../include/kthread.h"
#include "../include/kernel-private.h"
#include "../include/kchannel.h"

/* private menbers */

/* private functions */

/* public functions */


KChannel * newChannel(void)
{
    KChannel * result = malloc( sizeof(KChannel));
    if(result==0)
    {
        return 0;
    }

    result->empty = True;
    result->receiver = 0;

    return result;
}

void sendMessageToChannel(KChannel * channel, UInt32 message)
{
    KThread * th = channel->receiver;
    channel->message = message;
    channel->empty = False;

    if(th!=0)
    {
        channel->receiver = 0;
        setTaskAsReady(th);
    }
}

UInt32 waitMessageFromChannel(KChannel * channel)
{
    // no data, then wait...
    if( channel->empty == True)
    {
        channel->receiver = (KThread *)currentTask;
        setTaskAsBlocked();
    }

    channel->empty = True;

    return channel->message;
}

