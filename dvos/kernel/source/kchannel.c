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

